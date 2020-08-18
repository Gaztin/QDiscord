#include "Webhook.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Webhook::Webhook(const QJsonObject& data)
	: name_(data["name"].toString())
	, avatar_(data["avatar"].toString())
	, token_(data["token"].toString())
	, user_(data["user"].toObject())
	, id_(data["id"].toString().toULongLong())
	, guild_id_(data["guild_id"].toString().toULongLong())
	, channel_id_(data["channel_id"].toString().toULongLong())
{

}

Webhook::operator QJsonObject() const
{
	QJsonObject data;
	data["name"] = name_;
	data["avatar"] = avatar_;
	data["token"] = token_;
	data["user"] = QJsonObject(user_);
	data["id"] = QString::number(id_);
	data["guild_id"] = QString::number(guild_id_);
	data["channel_id"] = QString::number(channel_id_);

	return data;
}

QDISCORD_NAMESPACE_END