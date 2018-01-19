#include "VoiceState.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

VoiceState::VoiceState(const QJsonObject& data)
	: session_id_(data["session_id"].toString())
	, guild_id_(data["guild_id"].toString().toULongLong())
	, channel_id_(data["channel_id"].toString().toULongLong())
	, user_id_(data["user_id"].toString().toULongLong())
	, deaf_(data["deaf"].toBool())
	, mute_(data["mute"].toBool())
	, self_deaf_(data["self_deaf"].toBool())
	, self_mute_(data["self_mute"].toBool())
	, suppress_(data["suppress"].toBool())
{
}

QDISCORD_NAMESPACE_END