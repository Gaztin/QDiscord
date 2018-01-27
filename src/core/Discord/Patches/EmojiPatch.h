#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class EmojiPatch : public Patch
{
public:
	void setName(const QString& name);
	void setRoles(const QList<snowflake_t>& roles);
};

QDISCORD_NAMESPACE_END