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
