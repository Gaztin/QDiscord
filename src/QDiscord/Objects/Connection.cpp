#include "Connection.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Connection::Connection(const QJsonObject& data)
	: id_(data["id"].toString())
	, name_(data["name"].toString())
	, type_(data["type"].toString())
	, revoked_(data["revoked"].toBool())
{
	QJsonArray integrations_array = data["integrations"].toArray();
	for (QJsonValue integration_value : integrations_array)
	{
		integrations_.append(Integration(integration_value.toObject()));
	}
}

Connection::operator QJsonObject() const
{
	QJsonObject data;
	QJsonArray integrations_array;

	for (const Integration& integration : integrations_)
	{
		integrations_array.append(QJsonObject(integration));
	}

	data["integrations"] = integrations_array;
	data["id"] = id_;
	data["name"] = name_;
	data["type"] = type_;
	data["revoked"] = revoked_;

	return data;
}

QDISCORD_NAMESPACE_END