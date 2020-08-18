#pragma once
#include "Discord.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class GuildEmbed
{
public:
	explicit GuildEmbed(const QJsonObject& data);

	snowflake_t channelId() const { return channel_id_; }

	bool enabled() const { return enabled_; }

	operator QJsonObject() const;

private:
	snowflake_t channel_id_;

	bool enabled_;
};

QDISCORD_NAMESPACE_END