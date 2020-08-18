#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class RolePatch : public Patch
{
public:
	void setName(const QString& name);
	void setPermissions(int permissions);
	void setColor(int color);
	void setHoist(bool hoist);
	void setMentionable(bool mentionable);
};

QDISCORD_NAMESPACE_END