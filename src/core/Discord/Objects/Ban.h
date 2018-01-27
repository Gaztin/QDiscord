#pragma once
#include "Discord/Objects/User.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Ban
{
public:
	explicit Ban(const QJsonObject& data);

	const QString& reason() const { return reason_; }

	const User& user() const { return user_; }

	operator QJsonObject() const;

private:
	QString reason_;

	User user_;
};

QDISCORD_NAMESPACE_END