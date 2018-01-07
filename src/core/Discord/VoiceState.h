#pragma once
#include "Discord.h"

#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct VoiceState
{
	QString session_id;

	snowflake_t guild_id;
	snowflake_t channel_id;
	snowflake_t user_id;

	bool deaf;
	bool mute;
	bool self_deaf;
	bool self_mute;
	bool suppress;
};

QDISCORD_NAMESPACE_END