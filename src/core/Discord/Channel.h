#pragma once
#include "Discord/Overwrite.h"
#include "Discord/User.h"

#include <QtCore/QList>

QDISCORD_NAMESPACE_BEGIN

enum class ChannelType
{
	GUILD_TEXT = 0,
	DM,
	GUILD_VOICE,
	GROUP_DM,
	GUILD_CATEGORY,
};

struct Channel
{
	QList<Overwrite> permission_overwrites;
	QList<User> recipients;

	QString name;
	QString topic;
	QString icon;

	ChannelType type;

	snowflake_t id;
	snowflake_t guild_id;
	snowflake_t owner_id;
	snowflake_t application_id;
	snowflake_t last_message_id;

	int position;
	int bitrate;
	int user_limit;
};

QDISCORD_NAMESPACE_END