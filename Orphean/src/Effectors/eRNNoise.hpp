#pragma once

#include "Effector.hpp"
#include <RNNoise/RNNoise.h>

namespace Orphean
{
	class ERNNoise : public Effector
	{
		RNNoise* m_rnnoise = nullptr;
		QString m_modelName;

		constexpr static auto Name = u8"RNNoise";
		constexpr static auto BuildinModel = u8"build-in_model";
	public:
		~ERNNoise() {
			if (m_rnnoise != nullptr) {
				delete m_rnnoise;
			}
		}

		size_t doEffect(float* effect, size_t len) override {
			if (m_rnnoise == nullptr) return 0;
			return len;
		}
		
		void loadSettings(const QSettings& settings) override {
			auto v = settings.value(getEffectorName());
			if (v.isNull()) {
				m_modelName = BuildinModel;
			}
			else {
				m_modelName = v.toString();
			}
		}

		void saveSettings(QSettings& settings) const override {
			settings.setValue(getEffectorName(), qVariantFromValue(m_modelName));
		}

		QString getEffectorName() const override {
			return Name;
		}
	};
}