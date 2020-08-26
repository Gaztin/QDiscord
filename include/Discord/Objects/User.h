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
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class User
{
public:
	explicit User(const QJsonObject& data);

	const QString& username() const { return username_; }
	const QString& discriminator() const { return discriminator_; }
	const QString& avatar() const { return avatar_; }
	const QString& email() const { return email_; }
	
	snowflake_t id() const { return id_; }
	
	bool bot() const { return bot_; }
	bool mfaEnabled() const { return mfa_enabled_; }
	bool verified() const { return verified_; }

	operator QJsonObject() const;

private:
	QString username_;
	QString discriminator_;
	QString avatar_;
	QString email_;
	
	snowflake_t id_;
	
	bool bot_;
	bool mfa_enabled_;
	bool verified_;
};

QDISCORD_NAMESPACE_END
