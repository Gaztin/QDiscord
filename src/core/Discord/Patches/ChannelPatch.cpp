#include "ChannelPatch.h"

#include <QtCore/QJsonArray>
#include <QtCore/QList>

QDISCORD_NAMESPACE_BEGIN

void ChannelPatch::addPermissionOverwrite(
		const Overwrite& permission_overwrite)
{
	QJsonObject::const_iterator permission_overwrite_iterator =
		data_.find("permission_overwrites");
	QJsonArray permission_overwrites_array;
	if (permission_overwrite_iterator != data_.constEnd())
	{
		permission_overwrites_array = permission_overwrite_iterator->toArray();
	}

	permission_overwrites_array.append(QJsonObject(permission_overwrite));
	data_["permission_overwrites"] = permission_overwrites_array;
}

void ChannelPatch::setPermissionOverwrites(
		const QList<Overwrite>& permission_overwrites)
{
	QJsonArray permission_overwrites_array;
	for (const Overwrite& permission_overwrite : permission_overwrites)
	{
		QJsonObject permission_overwrite_object(permission_overwrite);
		permission_overwrites_array.append(permission_overwrite_object);
	}

	data_["permission_overwrites"] = permission_overwrites_array;
}

void ChannelPatch::setName(const QString& name)
{
	data_["name"] = name;
}

void ChannelPatch::setTopic(const QString& topic)
{
	data_["topic"] = topic;
}

void ChannelPatch::setParentId(snowflake_t parent_id)
{
	data_["parent_id"] = QString::number(parent_id);
}

void ChannelPatch::setPosition(int position)
{
	data_["position"] = position;
}

void ChannelPatch::setBitrate(int bitrate)
{
	data_["bitrate"] = bitrate;
}

void ChannelPatch::setUserLimit(int user_limit)
{
	data_["user_limit"] = user_limit;
}

void ChannelPatch::setNsfw(bool nsfw)
{
	data_["nsfw"] = nsfw;
}

QDISCORD_NAMESPACE_END