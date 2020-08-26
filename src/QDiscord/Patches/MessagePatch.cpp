#include "Discord/Patches/MessagePatch.h"

#include "Discord/Objects/Embed.h"

QDISCORD_NAMESPACE_BEGIN

void MessagePatch::setContent(const QString& content)
{
	data_["content"] = content;
}

void MessagePatch::setEmbed(const Embed& embed)
{
	data_["embed"] = QJsonObject(embed);
}

QDISCORD_NAMESPACE_END
