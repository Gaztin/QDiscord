#include "Invite.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

InviteMetadata::InviteMetadata(const QJsonObject& data)
	: created_at_(QDateTime::fromString(data["created_at"].toString(),
		Qt::ISODate))
	, inviter_(data["inviter"].toObject())
	, uses_(data["uses"].toInt())
	, max_uses_(data["max_uses"].toInt())
	, max_age_(data["max_age"].toInt())
	, temporary_(data["temporary"].toBool())
	, revoked_(data["revoked"].toBool())
{
}

InviteMetadata::operator QJsonObject() const
{
	QJsonObject data;
	data["created_at"] = created_at_.toString();
	data["inviter"] = QJsonObject(inviter_);
	data["uses"] = uses_;
	data["max_uses"] = max_uses_;
	data["max_age"] = max_age_;
	data["temporary"] = temporary_;
	data["revoked"] = revoked_;

	return data;
}

Invite::Invite(const QJsonObject& data)
	: code_(data["code"].toString())
	, guild_(data["guild"].toObject())
	, channel_(data["channel"].toObject())
	, metadata_(data)
{
}

Invite::operator QJsonObject() const
{
	QJsonObject data;
	data["code"] = code_;
	data["guild"] = QJsonObject(guild_);
	data["channel"] = QJsonObject(channel_);

	return data;
}

QDISCORD_NAMESPACE_END