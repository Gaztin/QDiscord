#pragma once
#include "Discord/Activity.h"
#include "Discord/Attachment.h"
#include "Discord/Channel.h"
#include "Discord/Embed.h"
#include "Discord/Emoji.h"
#include "Discord/Guild.h"
#include "Discord/GuildMember.h"
#include "Discord/Message.h"
#include "Discord/Overwrite.h"
#include "Discord/PresenceUpdate.h"
#include "Discord/Reaction.h"
#include "Discord/Role.h"
#include "Discord/User.h"
#include "Discord/VoiceState.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

namespace Serializer
{
	extern Activity activity(const QJsonObject& data);
	extern Attachment attachment(const QJsonObject& data);
	extern Channel channel(const QJsonObject& data);
	extern Embed embed(const QJsonObject& data);
	extern Emoji emoji(const QJsonObject& data);
	extern Guild guild(const QJsonObject& data);
	extern GuildMember guildMember(const QJsonObject& data);
	extern Message message(const QJsonObject& data);
	extern Overwrite overwrite(const QJsonObject& data);
	extern PresenceUpdate presenceUpdate(const QJsonObject& data);
	extern Reaction reaction(const QJsonObject& data);
	extern Role role(const QJsonObject& data);
	extern User user(const QJsonObject& data);
	extern VoiceState voiceState(const QJsonObject& data);
}

QDISCORD_NAMESPACE_END