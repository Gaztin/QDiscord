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

	Attachment attachment(const QJsonObject& data)
	{
		Attachment a;
		a.id = snowflake(data["id"]);
		a.filename = data["filename"].toString();
		a.size = data["size"].toInt();
		a.url = data["url"].toString();
		a.proxy_url = data["proxy_url"].toString();
		a.height = data["height"].toInt();
		a.width = data["width"].toInt();

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

	Embed embed(const QJsonObject& data)
	{
		Embed e;
		e.title = data["title"].toString();
		e.type = data["type"].toString();
		e.description = data["description"].toString();
		e.url = data["url"].toString();
		e.timestamp = timestamp(data["timestamp"]);
		e.color = data["color"].toInt();

		const QJsonObject& footer_data = data["footer"].toObject();
		e.footer.text = footer_data["text"].toString();
		e.footer.icon_url = footer_data["icon_url"].toString();
		e.footer.proxy_icon_url = footer_data["proxy_icon_url"].toString();

		const QJsonObject& image_data = data["image"].toObject();
		e.image.url = image_data["url"].toString();
		e.image.proxy_url = image_data["proxy_url"].toString();
		e.image.height = image_data["height"].toInt();
		e.image.width = image_data["width"].toInt();

		const QJsonObject& thumbnail_data = data["thumbnail"].toObject();
		e.thumbnail.url = thumbnail_data["url"].toString();
		e.thumbnail.proxy_url = thumbnail_data["proxy_url"].toString();
		e.thumbnail.height = thumbnail_data["height"].toInt();
		e.thumbnail.width = thumbnail_data["width"].toInt();

		const QJsonObject& video_data = data["video"].toObject();
		e.video.url = video_data["url"].toString();
		e.video.height = video_data["height"].toInt();
		e.video.width = video_data["width"].toInt();

		const QJsonObject& provider_data = data["provider"].toObject();
		e.provider.name = provider_data["name"].toString();
		e.provider.url = provider_data["url"].toString();

		const QJsonObject& author_data = data["author"].toObject();
		e.author.name = author_data["name"].toString();
		e.author.url = author_data["url"].toString();
		e.author.icon_url = author_data["icon_url"].toString();
		e.author.proxy_icon_url = author_data["proxy_icon_url"].toString();

		const QJsonArray& fields_data = data["fields"].toArray();
		e.fields.reserve(fields_data.size());
		for (const QJsonValue& field_value : fields_data)
		{
			const QJsonObject& field_data = field_value.toObject();
			EmbedField field;
			field.name = field_data["name"].toString();
			field.value = field_data["value"].toString();
			field.display_inline = field_data["inline"].toBool();
			e.fields.append(field);
		}

		return e;
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

	Message message(const QJsonObject& data)
	{
		Message m;
		m.id = snowflake(data["id"]);
		m.channel_id = snowflake(data["channel_id"]);
		m.author = user(data["author"].toObject());
		m.content = data["content"].toString();
		m.timestamp = timestamp(data["timestamp"]);
		m.edited_timestamp = timestamp(data["edited_timestamp"]);
		m.tts = data["tts"].toBool();
		m.mention_everyone = data["mention_everyone"].toBool();
		
		const QJsonArray& mentions_data = data["mentions"].toArray();
		m.mentions.reserve(mentions_data.size());
		for (const QJsonValue& mention_value : mentions_data)
		{
			m.mentions.append(user(mention_value.toObject()));
		}

		const QJsonArray& mention_roles_data = data["mention_roles"].toArray();
		m.mention_roles.reserve(mention_roles_data.size());
		for (const QJsonValue& mention_role_value : mention_roles_data)
		{
			m.mention_roles.append(role(mention_role_value.toObject()));
		}

		const QJsonArray& attachments_data = data["attachments"].toArray();
		m.attachments.reserve(attachments_data.size());
		for (const QJsonValue& attachment_value : attachments_data)
		{
			m.attachments.append(attachment(attachment_value.toObject()));
		}

		const QJsonArray& embeds_data = data["embeds"].toArray();
		m.embeds.reserve(embeds_data.size());
		for (const QJsonValue& embed_value : embeds_data)
		{
			m.embeds.append(embed(embed_value.toObject()));
		}

		const QJsonArray& reaction_data = data["reactions"].toArray();
		m.reactions.reserve(reaction_data.size());
		for (const QJsonValue& reaction_value : reaction_data)
		{
			m.reactions.append(reaction(reaction_value.toObject()));
		}

		m.nonce = snowflake(data["nonce"]);
		m.pinned = data["pinned"].toBool();
		m.webhook_id = data["webhook_id"].toString();
		m.type = static_cast<MessageType>(data["type"].toInt());

		return m;
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
		PresenceUpdate pu;
		pu.user = user(data["user"].toObject());
		pu.roles = array<snowflake_t>(data["roles"].toArray());
		pu.game = activity(data["game"].toObject());
		pu.guild_id = snowflake(data["guild_id"]);
		pu.status = data["status"].toString();

		return pu;
	}
	
	Reaction reaction(const QJsonObject& data)
	{
		Reaction r;
		r.count = data["count"].toInt();
		r.me = data["me"].toBool();
		r.emoji = emoji(data["emoji"].toObject());

		return r;
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

	snowflake_t snowflake(const QJsonValue& value)
	{
		return value.toString().toULongLong();
	}

	QDateTime timestamp(const QJsonValue& value)
	{
		return QDateTime::fromString(value.toString(), Qt::ISODate);
	}
}

QDISCORD_NAMESPACE_END