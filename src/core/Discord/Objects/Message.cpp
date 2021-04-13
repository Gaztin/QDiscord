#include "Message.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Message::Message(const QJsonObject& data)
	: timestamp_(QDateTime::fromString(data["timestamp"].toString(),
		Qt::ISODate))
	, edited_timestamp_(QDateTime::fromString(
		data["edited_timestamp"].toString(),Qt::ISODate))
	, content_(data["content"].toString())
	, webhook_id_(data["webhook_id"].toString())
	, author_(data["author"].toObject())
	, type_(static_cast<MessageType>(data["type"].toInt()))
	, id_(data["id"].toString().toULongLong())
	, channel_id_(data["channel_id"].toString().toULongLong())
	, guild_id_(data["guild_id"].toString().toULongLong())
	, nonce_(data["nonce"].toString().toULongLong())
	, tts_(data["tts"].toBool())
	, mention_everyone_(data["mention_everyone"].toBool())
	, pinned_(data["pinned"].toBool())
{
	QJsonArray mentions_array = data["mentions"].toArray();
	for (QJsonValue mention_value : mentions_array)
	{
		mentions_.append(User(mention_value.toObject()));
	}
	
	QJsonArray mention_roles_array = data["mention_roles"].toArray();
	for (QJsonValue mention_role_value : mention_roles_array)
	{
		mention_roles_.append(mention_role_value.toString().toULongLong());
	}
	
	QJsonArray attachments_array = data["attachments"].toArray();
	for (QJsonValue attachment_value : attachments_array)
	{
		attachments_.append(Attachment(attachment_value.toObject()));
	}
	
	QJsonArray embeds_array = data["embeds"].toArray();
	for (QJsonValue embed_value : embeds_array)
	{
		embeds_.append(Embed(embed_value.toObject()));
	}
	
	QJsonArray reactions_array = data["reactions"].toArray();
	for (QJsonValue reaction_value : reactions_array)
	{
		reactions_.append(Reaction(reaction_value.toObject()));
	}
}

QDISCORD_NAMESPACE_END