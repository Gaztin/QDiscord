#include "Guild.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Guild::Guild(const QJsonObject& data)
	: joined_at_(QDateTime::fromString(data["joined_at"].toString()))
	, name_(data["name"].toString())
	, icon_(data["icon"].toString())
	, splash_(data["splash"].toString())
	, region_(data["region"].toString())
	, verification_level_(static_cast<VerificationLevel>(
		data["verification_level"].toInt()))
	, default_message_notifications_(
		static_cast<DefaultMessageNotificationLevel>(
			data["default_message_notifications"].toInt()))
	, explicit_content_filter_(static_cast<ExplicitContentFilterLevel>(
		data["explicit_content_filter"].toInt()))
	, mfa_level_(static_cast<MultiFactorAuthenticationLevel>(
		data["mfa_level_"].toInt()))
	, id_(data["id"].toString().toULongLong())
	, owner_id_(data["owner_id"].toString().toULongLong())
	, afk_channel_id_(data["afk_channel_id"].toString().toULongLong())
	, embed_channel_id_(data["embed_channel_id"].toString().toULongLong())
	, application_id_(data["application_id"].toString().toULongLong())
	, widget_channel_id_(data["widget_channel_id"].toString().toULongLong())
	, afk_timeout_(data["afk_timeout"].toInt())
	, member_count_(data["member_count"].toInt())
	, embed_enabled_(data["embed_enabled"].toBool())
	, widget_enabled_(data["widget_enabled"].toBool())
	, large_(data["large"].toBool())
	, unavailable_(data["unavailable"].toBool())
{
	QJsonArray roles_array = data["roles"].toArray();
	for (QJsonValue role_value : roles_array)
	{
		roles_.append(Role(role_value.toObject()));
	}

	QJsonArray emojis_array = data["emojis"].toArray();
	for (QJsonValue emoji_value : emojis_array)
	{
		emojis_.append(Emoji(emoji_value.toObject()));
	}

	QJsonArray voice_states_array = data["voice_states"].toArray();
	for (QJsonValue voice_state_value : voice_states_array)
	{
		voice_states_.append(VoiceState(voice_state_value.toObject()));
	}

	QJsonArray members_array = data["members"].toArray();
	for (QJsonValue member_value : members_array)
	{
		members_.append(GuildMember(member_value.toObject()));
	}

	QJsonArray channels_array = data["channels"].toArray();
	for (QJsonValue channel_value : channels_array)
	{
		channels_.append(Channel(channel_value.toObject()));
	}

	QJsonArray presences_array = data["presences"].toArray();
	for (QJsonValue presence_value : presences_array)
	{
		presences_.append(PresenceUpdate(presence_value.toObject()));
	}

	QJsonArray features_array = data["features"].toArray();
	for (QJsonValue feature_value : features_array)
	{
		features_.append(feature_value.toString());
	}
}

Guild::operator QJsonObject() const
{
	QJsonObject data;
	data["joined_at"] = joined_at_.toString();
	data["name"] = name_;
	data["icon"] = icon_;
	data["splash"] = splash_;
	data["region"] = region_;
	data["verification_level"] = static_cast<int>(verification_level_);
	data["default_message_notifications"] = static_cast<int>(default_message_notifications_);
	data["explicit_content_filter"] = static_cast<int>(explicit_content_filter_);
	data["mfa_level_"] = static_cast<int>(mfa_level_);
	data["id"] = QString::number(id_);
	data["owner_id"] = QString::number(owner_id_);
	data["afk_channel_id"] = QString::number(afk_channel_id_);
	data["embed_channel_id"] = QString::number(embed_channel_id_);
	data["application_id"] = QString::number(application_id_);
	data["widget_channel_id"] = QString::number(widget_channel_id_);
	data["afk_timeout"] = afk_timeout_;
	data["member_count"] = member_count_;
	data["embed_enabled"] = embed_enabled_;
	data["widget_enabled"] = widget_enabled_;
	data["large"] = large_;
	data["unavailable"] = unavailable_;

	return data;
}

QDISCORD_NAMESPACE_END