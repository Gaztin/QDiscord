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
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

namespace Permissions
{
	enum
	{
		CREATE_INSTANT_INVITE      = 0x00000001,
		KICK_MEMBERS               = 0x00000002,
		BAN_MEMBERS                = 0x00000004,
		ADMINISTRATOR              = 0x00000008,
		MANAGE_CHANNELS            = 0x00000010,
		MANAGE_GUILD               = 0x00000020,
		ADD_REACTIONS              = 0x00000040,
		VIEW_AUDIT_LOG             = 0x00000080,
		VIEW_CHANNEL               = 0x00000400,
		SEND_MESSAGES              = 0x00000800,
		SEND_TTS_MESSAGES          = 0x00001000,
		MANAGE_MESSAGES            = 0x00002000,
		EMBED_LINKS                = 0x00004000,
		ATTACH_FILES               = 0x00008000,
		READ_MESSAGE_HISTORY       = 0x00010000,
		MENTION_EVERYONE           = 0x00020000,
		USE_EXTERNAL_EMOJIS        = 0x00040000,
		CONNECT                    = 0x00100000,
		SPEAK                      = 0x00200000,
		MUTE_MEMBERS               = 0x00400000,
		DEAFEN_MEMBERS             = 0x00800000,
		MOVE_MEMBERS               = 0x01000000,
		USE_VAD                    = 0x02000000,
		CHANGE_NICKNAME            = 0x04000000,
		MANAGE_NICKNAMES           = 0x08000000,
		MANAGE_ROLES               = 0x10000000,
		MANAGE_WEBHOOKS            = 0x20000000,
		MANAGE_EMOJIS              = 0x40000000
	};
}

class Role
{
public:
	explicit Role(const QJsonObject& data);

	const QString& name() const { return name_; }
	
	snowflake_t id() const { return id_; }
	
	int color() const { return color_; }
	int position() const { return position_; }
	int permissions() const { return permissions_; }
	
	bool hoist() const { return hoist_; }
	bool managed() const { return managed_; }
	bool mentionable() const { return mentionable_; }

	operator QJsonObject() const;

private:
	QString name_;
	
	snowflake_t id_;
	
	int color_;
	int position_;
	int permissions_;
	
	bool hoist_;
	bool managed_;
	bool mentionable_;
};

QDISCORD_NAMESPACE_END
