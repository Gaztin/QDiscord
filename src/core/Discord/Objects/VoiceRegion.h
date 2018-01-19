#pragma once
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class VoiceRegion
{
public:
	explicit VoiceRegion(const QJsonObject& data);

	operator QJsonObject() const;

	const QString& id() const { return id_; }
	const QString& name() const { return name_; }
	const QString& sampleHostname() const { return sample_hostname_; }

	int samplePort() const { return sample_port_; }

	bool vip() const { return vip_; }
	bool optimal() const { return optimal_; }
	bool deprecated() const { return deprecated_; }
	bool custom() const { return custom_; }

private:
	QString id_;
	QString name_;
	QString sample_hostname_;

	int sample_port_;

	bool vip_;
	bool optimal_;
	bool deprecated_;
	bool custom_;
};

QDISCORD_NAMESPACE_END