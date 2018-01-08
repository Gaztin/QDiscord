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

class QJsonArray;
class QJsonObject;
class QJsonValue;

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

	extern snowflake_t snowflake(const QJsonValue& value);
	extern QDateTime timestamp(const QJsonValue& value);

	template<typename T>
	inline T object(const QJsonObject& data);

	template<typename T>
	inline T value(const QJsonValue& data);

	template<typename T>
	inline QList<T> array(const QJsonArray& data);
}

template<typename T>
inline T Serializer::object(const QJsonObject& data)
{
	static_assert("Unserializable object type");
}

template<>
inline Activity Serializer::object<Activity>(const QJsonObject& data)
{
	return Serializer::activity(data);
}

template<>
inline Attachment Serializer::object<Attachment>(const QJsonObject& data)
{
	return Serializer::attachment(data);
}

template<>
inline Channel Serializer::object<Channel>(const QJsonObject& data)
{
	return Serializer::channel(data);
}

template<>
inline Embed Serializer::object<Embed>(const QJsonObject& data)
{
	return Serializer::embed(data);
}

template<>
inline Emoji Serializer::object<Emoji>(const QJsonObject& data)
{
	return Serializer::emoji(data);
}

template<>
inline Guild Serializer::object<Guild>(const QJsonObject& data)
{
	return Serializer::guild(data);
}

template<>
inline GuildMember Serializer::object<GuildMember>(const QJsonObject& data)
{
	return Serializer::guildMember(data);
}

template<>
inline Message Serializer::object<Message>(const QJsonObject& data)
{
	return Serializer::message(data);
}

template<>
inline Overwrite Serializer::object<Overwrite>(const QJsonObject& data)
{
	return Serializer::overwrite(data);
}

template<>
inline PresenceUpdate Serializer::object<PresenceUpdate>(
		const QJsonObject& data)
{
	return Serializer::presenceUpdate(data);
}

template<>
inline Reaction Serializer::object<Reaction>(const QJsonObject& data)
{
	return Serializer::reaction(data);
}

template<>
inline Role Serializer::object<Role>(const QJsonObject& data)
{
	return Serializer::role(data);
}

template<>
inline User Serializer::object<User>(const QJsonObject& data)
{
	return Serializer::user(data);
}

template<>
inline VoiceState Serializer::object<VoiceState>(const QJsonObject& data)
{
	return Serializer::voiceState(data);
}

template<typename T>
inline T Serializer::value(const QJsonValue& data)
{
	return Serializer::object<T>(data.toObject());
}

template<>
inline snowflake_t Serializer::value<snowflake_t>(const QJsonValue& data)
{
	return Serializer::snowflake(data);
}

template<>
inline QDateTime Serializer::value<QDateTime>(const QJsonValue& data)
{
	return Serializer::timestamp(data);
}

template<typename T>
inline QList<T> Serializer::array(const QJsonArray& data)
{
	QList<T> l;
	l.reserve(data.size());
	for (int i = 0; i < data.size(); ++i)
	{
		l.append(Serializer::value<T>(data[i]));
	}
	return l;
}

QDISCORD_NAMESPACE_END