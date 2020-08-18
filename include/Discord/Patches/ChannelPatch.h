#pragma once
#include "Discord/Objects/Overwrite.h"
#include "Discord/Patches/Patch.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

class ChannelPatch : public Patch
{
public:
	void addPermissionOverwrite(const Overwrite& permission_overwrite);
	void setPermissionOverwrites(
		const QList<Overwrite>& permission_overwrites);

	void setName(const QString& name);
	void setTopic(const QString& topic);

	void setParentId(snowflake_t parent_id);

	void setPosition(int position);
	void setBitrate(int bitrate);
	void setUserLimit(int user_limit);

	void setNsfw(bool nsfw);
};

QDISCORD_NAMESPACE_END