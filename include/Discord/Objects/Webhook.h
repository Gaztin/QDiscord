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
#include "Discord/Objects/User.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Webhook
{
public:
	explicit Webhook(const QJsonObject& data);

	const QString& name() const { return name_; }
	const QString& avatar() const { return avatar_; }
	const QString& token() const { return token_; }

	const User& user() const { return user_; }

	snowflake_t id() const { return id_; }
	snowflake_t guildId() const { return guild_id_; }
	snowflake_t channelId() const { return channel_id_; }

	operator QJsonObject() const;

private:
	QString name_;
	QString avatar_;
	QString token_;

	User user_;

	snowflake_t id_;
	snowflake_t guild_id_;
	snowflake_t channel_id_;
};

QDISCORD_NAMESPACE_END
