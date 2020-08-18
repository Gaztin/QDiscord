#include "GuildEmbed.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

GuildEmbed::GuildEmbed(const QJsonObject& data)
	: channel_id_(data["channel_id"].toString().toULongLong())
	, enabled_(data["enabled"].toBool())
{
}

GuildEmbed::operator QJsonObject() const
{
	QJsonObject data;
	data["channel_id"] = QString::number(channel_id_);
	data["enabled"] = enabled_;

	return data;
}

QDISCORD_NAMESPACE_END