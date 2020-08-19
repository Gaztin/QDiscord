#include "Channel.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Channel::Channel(const QJsonObject& data)
	: name_(data["name"].toString())
	, topic_(data["topic"].toString())
	, icon_(data["icon"].toString())
	, type_(static_cast<ChannelType>(data["type"].toInt()))
	, id_(data["id"].toString().toULongLong())
	, guild_id_(data["guild_id"].toString().toULongLong())
	, owner_id_(data["owner_id"].toString().toULongLong())
	, application_id_(data["application_id"].toString().toULongLong())
	, last_message_id_(data["last_message_id"].toString().toULongLong())
	, parent_id_(data["parent_id"].toString().toULongLong())
	, position_(data["position"].toInt())
	, bitrate_(data["bitrate"].toInt())
	, user_limit_(data["user_limit"].toInt())
	, rate_limit_per_user_(data["rate_limit_per_user"].toInt())
	, nsfw_(data["nsfw"].toBool())
{
	QJsonArray permission_overwrites_array =
		data["permission_overwrites"].toArray();
	for (QJsonValue permission_overwrites_value :
			permission_overwrites_array)
	{
		permission_overwrites_.append(Overwrite(
			permission_overwrites_value.toObject()));
	}

	QJsonArray recipients_array = data.value("recipients").toArray();
	for (QJsonValue recipients_value : recipients_array)
	{
		recipients_.append(User(recipients_value.toObject()));
	}
}

Channel::operator QJsonObject() const
{
	QJsonObject data;
	data["name"] = name_;
	data["topic"] = topic_;
	data["icon"] = icon_;
	data["type"] = static_cast<int>(type_);
	data["id"] = QString::number(id_);
	data["guild_id"] = QString::number(guild_id_);
	data["owner_id"] = QString::number(owner_id_);
	data["application_id"] = QString::number(application_id_);
	data["last_message_id"] = QString::number(last_message_id_);
	data["position"] = position_;
	data["bitrate"] = bitrate_;
	data["user_limit"] = user_limit_;

	return data;
}

QDISCORD_NAMESPACE_END