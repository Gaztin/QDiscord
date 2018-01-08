#include "Serializer.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

namespace Serializer
{
	Activity activity(const QJsonObject& data)
	{
		Activity a;
		a.name = data["name"].toString();
		a.type = static_cast<ActivityType>(data["type"].toInt());
		a.url = data["url"].toString();

		const QJsonObject& timestamps_data = data["timestamps"].toObject();
		a.timestamps.start = timestamps_data["start"].toInt();
		a.timestamps.end = timestamps_data["end"].toInt();

		a.application_id = snowflake(data["application_id"]);
		a.details = data["details"].toString();
		a.state = data["state"].toString();

		const QJsonObject& party_data = data["party"].toObject();
		a.party.id = party_data["id"].toString();

		const QJsonArray& party_size_data = party_data["size"].toArray();
		a.party.current_size = party_size_data[0].toInt();
		a.party.max_size = party_size_data[1].toInt();

		const QJsonObject& assets_data = data["assets"].toObject();
		a.assets.large_image = assets_data["large_image"].toString();
		a.assets.large_text = assets_data["large_text"].toString();
		a.assets.small_imgae = assets_data["small_image"].toString();
		a.assets.small_text = assets_data["small_text"].toString();

		return a;
	}

	Channel channel(const QJsonObject& data)
	{
		Channel c;
		c.id = data.value("id").toString().toULongLong();
		c.type = static_cast<ChannelType>(data.value("type").toInt());
		c.guild_id = data.value("guild_id").toString().toULongLong();
		c.position = data.value("position").toInt();

		QJsonArray permission_overwrites_array = data.value(
			"permission_overwrites").toArray();
		for (QJsonValue permission_overwrites_value :
				permission_overwrites_array)
		{
			c.permission_overwrites.append(overwrite(
				permission_overwrites_value.toObject()));
		}

		c.name = data.value("name").toString();
		c.topic = data.value("topic").toString();
		c.last_message_id = data.value(
			"last_message_id").toString().toULongLong();
		c.bitrate = data.value("bitrate").toInt();
		c.user_limit = data.value("user_limit").toInt();

		QJsonArray recipients_array = data.value("recipients").toArray();
		for (QJsonValue recipients_value : recipients_array)
		{
			c.recipients.append(user(recipients_value.toObject()));
		}

		c.icon = data.value("icon").toString();
		c.owner_id = data.value("owner_id").toString().toULongLong();
		c.application_id = data.value(
			"application_id").toString().toULongLong();

		return c;
	}
	
	Emoji emoji(const QJsonObject& data)
	{
		Emoji e;
		e.id = data.value("id").toString().toULongLong();
		e.name = data.value("name").toString();

		QJsonArray roles_array = data.value("roles").toArray();
		for (QJsonValue roles_value : roles_array)
		{
			e.roles.append(role(roles_value.toObject()));
		}

		e.require_colons = data.value("require_colons").toBool();
		e.managed = data.value("managed").toBool();

		return e;
	}
	
	Guild guild(const QJsonObject& data)
	{
		Guild g;
		g.id = data.value("id").toString().toULongLong();
		g.name = data.value("name").toString();
		g.icon = data.value("icon").toString();
		g.splash = data.value("splash").toString();
		g.owner_id = data.value("owner_id").toString().toULongLong();
		g.region = data.value("region").toString();
		g.afk_channel_id = data.value(
			"afk_channel_id").toString().toULongLong();
		g.afk_timeout = data.value("afk_timeout").toInt();
		g.embed_enabled = data.value("embed_enabled").toBool();
		g.embed_channel_id = data.value(
			"embed_channel_id").toString().toULongLong();
		g.verification_level = static_cast<VerificationLevel>(data.value(
			"verification_level").toInt());
		g.default_message_notifications =
			static_cast<DefaultMessageNotificationLevel>(data.value(
				"default_message_notifications").toInt());
		g.explicit_content_filter = static_cast<ExplicitContentFilterLevel>(
			data.value("explicit_content_filter").toInt());

		QJsonArray roles_array = data.value("roles").toArray();
		for (QJsonValue roles_value : roles_array)
		{
			g.roles.append(role(roles_value.toObject()));
		}

		QJsonArray emojis_array = data.value("emojis").toArray();
		for (QJsonValue emojis_value : emojis_array)
		{
			g.emojis.append(emoji(emojis_value.toObject()));
		}

		QJsonArray features_array = data.value("features").toArray();
		for (QJsonValue features_value : features_array)
		{
			g.features.append(features_value.toString());
		}

		g.mfa_level = static_cast<MultiFactorAuthenticationLevel>(
			data.value("mfa_level").toInt());
		g.application_id = data.value(
			"application_id").toString().toULongLong();
		g.widget_enabled = data.value("widget_enabled").toBool();
		g.widget_channel_id = data.value(
			"widget_channel_id").toString().toULongLong();
		g.joined_at = QDateTime::fromString(data.value(
			"joined_at").toString(), Qt::ISODate);
		g.large = data.value("large").toBool();
		g.unavailable = data.value("unavailable").toBool();
		g.member_count = data.value("member_count").toInt();

		QJsonArray voice_states_array = data.value("voice_states").toArray();
		for (QJsonValue voice_states_value : voice_states_array)
		{
			g.voice_states.append(voiceState(
				voice_states_value.toObject()));
		}

		QJsonArray members_array = data.value("members").toArray();
		for (QJsonValue members_value : members_array)
		{
			g.members.append(guildMember(members_value.toObject()));
		}

		QJsonArray channels_array = data.value("channels").toArray();
		for (QJsonValue channels_value : channels_array)
		{
			g.channels.append(channel(channels_value.toObject()));
		}

		QJsonArray presences_array = data.value("presences").toArray();
		for (QJsonValue presences_value : presences_array)
		{
			g.presences.append(presenceUpdate(presences_value.toObject()));
		}

		return g;
	}
	
	GuildMember guildMember(const QJsonObject& data)
	{
		GuildMember gm;
		gm.user = user(data.value("user").toObject());
		gm.nick = data.value("nick").toString();

		QJsonArray roles_array = data.value("roles").toArray();
		for (QJsonValue roles_value : roles_array)
		{
			gm.roles.append(roles_value.toString().toULongLong());
		}

		gm.joined_at = QDateTime::fromString(data.value(
			"joined_at").toString(), Qt::ISODate);
		gm.deaf = data.value("deaf").toBool();
		gm.mute = data.value("mute").toBool();

		return gm;
	}
	
	Overwrite overwrite(const QJsonObject& data)
	{
		Overwrite o;
		o.id = data.value("id").toString().toULongLong();
		o.type = data.value("type").toString();
		o.allow = data.value("allow").toInt();
		o.deny = data.value("deny").toInt();

		return o;
	}
	
	PresenceUpdate presenceUpdate(const QJsonObject& data)
	{
		PresenceUpdate p;
		p.user = user(data.value("user").toObject());

		QJsonArray roles_array = data.value("roles").toArray();
		for (QJsonValue roles_value : roles_array)
		{
			p.roles.append(roles_value.toString().toULongLong());
		}

		p.game = game(data.value("game").toObject());
		p.guild_id = data.value("guild_id").toString().toULongLong();
		p.status = data.value("status").toString();

		return p;
	}
	
	Role role(const QJsonObject& data)
	{
		Role r;
		r.id = data.value("id").toString().toULongLong();
		r.name = data.value("name").toString();
		r.color = data.value("color").toInt();
		r.hoist = data.value("hoist").toBool();
		r.position = data.value("position").toInt();
		r.permissions = data.value("permissions").toInt();
		r.managed = data.value("managed").toBool();
		r.mentionable = data.value("mentionable").toBool();

		return r;
	}
	
	User user(const QJsonObject& data)
	{
		User u;
		u.id = data.value("id").toString().toULongLong();
		u.username = data.value("username").toString();
		u.discriminator = data.value("discriminator").toString();
		u.avatar = data.value("avatar").toString();
		u.bot = data.value("bot").toBool();
		u.mfa_enabled = data.value("mfa_enabled").toBool();
		u.verified = data.value("verified").toBool();
		u.email = data.value("email").toString();

		return u;
	}
	
	VoiceState voiceState(const QJsonObject& data)
	{
		VoiceState vs;
		vs.guild_id = data.value("guild_id").toString().toULongLong();
		vs.channel_id = data.value("channel_id").toString().toULongLong();
		vs.user_id = data.value("user_id").toString().toULongLong();
		vs.session_id = data.value("session_id").toString();
		vs.deaf = data.value("deaf").toBool();
		vs.mute = data.value("mute").toBool();
		vs.self_deaf = data.value("self_deaf").toBool();
		vs.self_mute = data.value("self_mute").toBool();
		vs.suppress = data.value("suppress").toBool();

		return vs;
	}
	
}

QDISCORD_NAMESPACE_END