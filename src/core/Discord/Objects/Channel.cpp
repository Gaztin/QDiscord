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
	, position_(data["position"].toInt())
	, bitrate_(data["bitrate"].toInt())
	, user_limit_(data["user_limit"].toInt())
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

QDISCORD_NAMESPACE_END