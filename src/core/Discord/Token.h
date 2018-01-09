#pragma once
#include "Discord.h"

#include <QtCore/QObject>

QDISCORD_NAMESPACE_BEGIN

class Token
{
public:
	enum class Type
	{
		UNKNOWN = -1,
		BOT = 0,
		OAUTH2_BEARER,
	};

	Token();

	void generate(const QString token_base, Type type);

	QByteArray authorization() const;

	const QString& tokenBase() const { return token_base_; }
	Type type() const { return type_; }

private:
	QString token_base_;
	Type type_;
};

QDISCORD_NAMESPACE_END