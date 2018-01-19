#pragma once
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class GuildMemberPatch : public Patch
{
public:
	void addRole(snowflake_t role);
	void setRoles(const QList<snowflake_t>& roles);

	void setNick(const QString& nick);

	void setChannelId(snowflake_t channel_id);

	void setMute(bool mute);
	void setDeaf(bool deaf);
};

QDISCORD_NAMESPACE_END