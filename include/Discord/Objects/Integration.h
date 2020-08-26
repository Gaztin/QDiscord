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

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class IntegrationAccount
{
public:
	explicit IntegrationAccount(const QJsonObject& data);

	const QString& id() const { return id_; }
	const QString& name() const { return name_; }

	operator QJsonObject() const;

private:
	QString id_;
	QString name_;
};

class Integration
{
public:
	explicit Integration(const QJsonObject& data);

	const QString& name() const { return name_; }
	const QString& type() const { return type_; }
	const QDateTime& syncedAt() const { return synced_at_; }

	const User& user() const { return user_; }
	const IntegrationAccount& account() const { return account_; }

	snowflake_t id() const { return id_; }
	snowflake_t roleId() const { return role_id_; }

	int expireBehavior() const { return expire_behavior_; }
	int expireGracePeriod() const { return expire_grace_period_; }

	bool enabled() const { return enabled_; }
	bool syncing() const { return syncing_; }

	operator QJsonObject() const;

private:
	QString name_;
	QString type_;
	QDateTime synced_at_;

	User user_;
	IntegrationAccount account_;

	snowflake_t id_;
	snowflake_t role_id_;

	int expire_behavior_;
	int expire_grace_period_;

	bool enabled_;
	bool syncing_;
};

QDISCORD_NAMESPACE_END
