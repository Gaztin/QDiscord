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

#include <QtCore/QDateTime>
#include <QtCore/QList>
#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class GuildMember
{
public:
	explicit GuildMember(const QJsonObject& data);

	const QList<snowflake_t>& roles() const { return roles_; }
	
	const QDateTime& joinedAt() const { return joined_at_; }
	const QString& nick() const { return nick_; }
	
	const User& user() const { return user_; }
	
	bool deaf() const { return deaf_; }
	bool mute() const { return mute_; }

private:
	QList<snowflake_t> roles_;
	
	QDateTime joined_at_;
	QString nick_;
	
	User user_;
	
	bool deaf_;
	bool mute_;
};

QDISCORD_NAMESPACE_END
