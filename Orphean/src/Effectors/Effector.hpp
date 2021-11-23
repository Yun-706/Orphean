#pragma once

#include <QString>
#include <QSettings>
#include <QSharedPointer>

namespace Orphean
{
	class Effector
	{
	public:
		virtual ~Effector() = default;

		//should return processed length
		virtual size_t doEffect(float* pcm, size_t len) = 0;

		virtual void loadSettings(const QSettings& settings) = 0;
		virtual void saveSettings(QSettings& settings) const = 0;

		virtual QString getEffectorName() const = 0;
	};

	using EffectorHandle = QSharedPointer<Effector>;

	template <typename T>
	static EffectorHandle CreateEffector() {
		return new T();
	}
}

