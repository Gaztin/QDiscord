#include "VoiceRegion.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

VoiceRegion::VoiceRegion(const QJsonObject& data)
	: id_(data["id"].toString())
	, name_(data["name"].toString())
	, sample_hostname_(data["sample_hostname"].toString())
	, sample_port_(data["sample_port"].toInt())
	, vip_(data["vip"].toBool())
	, optimal_(data["optimal"].toBool())
	, deprecated_(data["deprecated"].toBool())
	, custom_(data["custom"].toBool())
{
}

VoiceRegion::operator QJsonObject() const
{
	QJsonObject data;
	data["id"] = id_;
	data["name"] = name_;
	data["sample_hostname"] = sample_hostname_;
	data["sample_port"] = sample_port_;
	data["vip"] = vip_;
	data["optimal"] = optimal_;
	data["deprecated"] = deprecated_;
	data["custom"] = custom_;

	return data;
}

QDISCORD_NAMESPACE_END