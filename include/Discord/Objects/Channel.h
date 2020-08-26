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
#include "Discord/Objects/Overwrite.h"
#include "Discord/Objects/User.h"

#include <QtCore/QList>
#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

enum class ChannelType
{
	GUILD_TEXT = 0,
	DM,
	GUILD_VOICE,
	GROUP_DM,
	GUILD_CATEGORY,
};

class Channel
{
public:
	explicit Channel(const QJsonObject& data);

	const QList<Overwrite>& permissionOverwrites() const
		{ return permission_overwrites_; }
	const QList<User>& recipients() const { return recipients_; }
	
	const QString& name() const { return name_; }
	const QString& topic() const { return topic_; }
	const QString& icon() const { return icon_; }
	
	ChannelType type() const { return type_; }
	
	snowflake_t id() const { return id_; }
	snowflake_t guildId() const { return guild_id_; }
	snowflake_t ownerId() const { return owner_id_; }
	snowflake_t applicationId() const { return application_id_; }
	snowflake_t lastMessageId() const { return last_message_id_; }
	
	int position() const { return position_; }
	int bitrate() const { return bitrate_; }
	int userLimit() const { return user_limit_; }

	operator QJsonObject() const;

private:
	QList<Overwrite> permission_overwrites_;
	QList<User> recipients_;
	
	QString name_;
	QString topic_;
	QString icon_;
	
	ChannelType type_;
	
	snowflake_t id_;
	snowflake_t guild_id_;
	snowflake_t owner_id_;
	snowflake_t application_id_;
	snowflake_t last_message_id_;
	
	int position_;
	int bitrate_;
	int user_limit_;
};

QDISCORD_NAMESPACE_END
