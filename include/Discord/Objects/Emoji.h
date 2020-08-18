#pragma once
#include "Discord/Objects/Role.h"

#include <QtCore/QList>
#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Emoji
{
public:
	explicit Emoji(const QJsonObject& data);

	const QList<Role>& roles() const { return roles_; }
	const QString& name() const { return name_; }
	
	snowflake_t id() const { return id_; }
	
	bool requireColons() const { return require_colons_; }
	bool managed() const { return managed_; }

private:
	QList<Role> roles_;
	
	QString name_;
	
	snowflake_t id_;
	
	bool require_colons_;
	bool managed_;
};

QDISCORD_NAMESPACE_END