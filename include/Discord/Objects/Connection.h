#pragma once
#include "Discord/Objects/Integration.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Connection
{
public:
	explicit Connection(const QJsonObject& data);

	const QList<Integration>& integrations() const { return integrations_; }

	const QString& id() const { return id_; }
	const QString& name() const { return name_; }
	const QString& type() const { return type_; }

	bool revoked() const { return revoked_; }

	operator QJsonObject() const;
		
private:
	QList<Integration> integrations_;

	QString id_;
	QString name_;
	QString type_;

	bool revoked_;
};

QDISCORD_NAMESPACE_END