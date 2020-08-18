#pragma once
#include "Discord/Objects/Channel.h"
#include "Discord/Objects/Guild.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class InviteMetadata
{
public:
	explicit InviteMetadata(const QJsonObject& data);

	operator QJsonObject() const;

private:
	QDateTime created_at_;

	User inviter_;

	int uses_;
	int max_uses_;
	int max_age_;

	bool temporary_;
	bool revoked_;
};

class Invite
{
public:
	explicit Invite(const QJsonObject& data);

	const QString& code() const { return code_; }

	const Guild& guild() const { return guild_; }
	const Channel& channel() const { return channel_; }
	const InviteMetadata& metadata() const { return metadata_; }

	operator QJsonObject() const;

private:
	QString code_;

	Guild guild_;
	Channel channel_;
	InviteMetadata metadata_;
};

QDISCORD_NAMESPACE_END