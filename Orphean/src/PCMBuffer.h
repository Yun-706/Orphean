#pragma once

#include <list>
#include <mutex>

namespace Orphean
{
	class PCMBufferPool
	{
		std::mutex m_mutex;
		size_t m_bufferSize = 480;

		class PCMBufferInner
		{
			friend class PCMBufferPool;
			size_t m_size = 0;
			float* m_buffer = nullptr;
			PCMBufferInner(size_t size, float* buffer) : m_size(size), m_buffer(buffer) {}
		public:
			float* buffer() const { return m_buffer; }
			size_t size() const { return m_size; }
		};

		std::list<PCMBufferInner> m_buffers;
		PCMBufferPool() {};

		static PCMBufferPool& getInstance() {
			static PCMBufferPool inst;
			return inst;
		}

		~PCMBufferPool() {
			for (PCMBufferInner b : m_buffers) {
				delete b.m_buffer;
			}
		}

		PCMBufferInner getBuffer() {
			std::lock_guard<std::mutex> locker(m_mutex);
			if (m_buffers.empty()) {
				return PCMBufferInner(m_bufferSize, new float[m_bufferSize]);
			}
			else {
				auto h = m_buffers.front();
				m_buffers.pop_front();
				return h;
			}
		}

		void freeBuffer(PCMBufferInner bufferInner) {
			std::lock_guard<std::mutex> locker(m_mutex);
			m_buffers.push_back(bufferInner);
		}

		friend class PCMBuffer;
	};


	class PCMBuffer
	{
		PCMBufferPool::PCMBufferInner m_buffer;
	public:
		PCMBuffer() : m_buffer(PCMBufferPool::getInstance().getBuffer()) {}

		~PCMBuffer() {
			PCMBufferPool::getInstance().freeBuffer(m_buffer);
		}

		PCMBufferPool::PCMBufferInner operator -> () { return m_buffer; }
	};
}