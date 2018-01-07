#pragma once
#include "Discord/Channel.h"
#include "Discord/Emoji.h"
#include "Discord/Game.h"
#include "Discord/Guild.h"
#include "Discord/GuildMember.h"
#include "Discord/Overwrite.h"
#include "Discord/PresenceUpdate.h"
#include "Discord/Role.h"
#include "Discord/User.h"
#include "Discord/VoiceState.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

namespace Serializer
{
	extern Channel channel(const QJsonObject& data);
	extern Emoji emoji(const QJsonObject& data);
	extern Game game(const QJsonObject& data);
	extern Guild guild(const QJsonObject& data);
	extern GuildMember guildMember(const QJsonObject& data);
	extern Overwrite overwrite(const QJsonObject& data);
	extern PresenceUpdate presenceUpdate(const QJsonObject& data);
	extern Role role(const QJsonObject& data);
	extern User user(const QJsonObject& data);
	extern VoiceState voiceState(const QJsonObject& data);
}

QDISCORD_NAMESPACE_END