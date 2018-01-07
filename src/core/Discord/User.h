#pragma once
#include "Discord.h"

#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct User
{
	QString username;
	QString discriminator;
	QString avatar;
	QString email;

	snowflake_t id;

	bool bot;
	bool mfa_enabled;
	bool verified;
};

QDISCORD_NAMESPACE_END