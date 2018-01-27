#include "Integration.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

IntegrationAccount::IntegrationAccount(const QJsonObject& data)
	: id_(data["id"].toString())
	, name_(data["name"].toString())
{
}

IntegrationAccount::operator QJsonObject() const
{
	QJsonObject data;
	data["id"] = id_;
	data["name"] = name_;

	return data;
}

Integration::Integration(const QJsonObject& data)
	: name_(data["name"].toString())
	, type_(data["type"].toString())
	, synced_at_(QDateTime::fromString(data["synced_at"].toString(), Qt::ISODate))
	, user_(data["user"].toObject())
	, account_(data["account"].toObject())
	, id_(data["id"].toString().toULongLong())
	, role_id_(data["role_id"].toString().toULongLong())
	, expire_behavior_(data["expire_behavior"].toInt())
	, expire_grace_period_(data["expire_grace_period"].toInt())
	, enabled_(data["enabled"].toBool())
	, syncing_(data["syncing"].toBool())
{
}

Integration::operator QJsonObject() const
{
	QJsonObject data;
	data["name"] = name_;
	data["type"] = type_;
	data["synced_at"] = synced_at_.toString();
	data["user"] = QJsonObject(user_);
	data["account"] = QJsonObject(account_);
	data["id"] = QString::number(id_);
	data["role_id"] = QString::number(role_id_);
	data["expire_behavior"] = expire_behavior_;
	data["expire_grace_period"] = expire_grace_period_;
	data["enabled"] = enabled_;
	data["syncing"] = syncing_;

	return data;
}

QDISCORD_NAMESPACE_END