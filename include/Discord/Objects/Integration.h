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