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
