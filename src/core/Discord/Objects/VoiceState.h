#pragma once
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class VoiceState
{
public:
	explicit VoiceState(const QJsonObject& data);

	const QString& sessionId() const { return session_id_; }
	
	snowflake_t guildId() const { return guild_id_; }
	snowflake_t channelId() const { return channel_id_; }
	snowflake_t userId() const { return user_id_; }
	
	bool deaf() const { return deaf_; }
	bool mute() const { return mute_; }
	bool selfDeaf() const { return self_deaf_; }
	bool selfMute() const { return self_mute_; }
	bool suppress() const { return suppress_; }

private:
	QString session_id_;
	
	snowflake_t guild_id_;
	snowflake_t channel_id_;
	snowflake_t user_id_;
	
	bool deaf_;
	bool mute_;
	bool self_deaf_;
	bool self_mute_;
	bool suppress_;
};

QDISCORD_NAMESPACE_END