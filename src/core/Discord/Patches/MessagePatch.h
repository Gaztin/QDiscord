#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class Embed;

class MessagePatch : public Patch
{
public:
	void setContent(const QString& content);
	void setEmbed(const Embed& embed);
};

QDISCORD_NAMESPACE_END