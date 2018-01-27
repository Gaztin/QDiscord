#include "WebhookPatch.h"

QDISCORD_NAMESPACE_BEGIN

void WebhookPatch::setName(const QString& name)
{
	data_["name"] = name;
}

void WebhookPatch::setAvatar(const QByteArray& avatar)
{
	data_["avatar"] = QString(avatar);
}

void WebhookPatch::setChannelId(snowflake_t channel_id)
{
	data_["channel_id"] = QString::number(channel_id);
}

QDISCORD_NAMESPACE_END