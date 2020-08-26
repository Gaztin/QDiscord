/*
 * Copyright (c) 2020 Sebastian Kylander https://gaztin.com/
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will
 * the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
 *    being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

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
