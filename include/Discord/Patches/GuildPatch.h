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
#include "Discord/Patches/Patch.h"

QDISCORD_NAMESPACE_BEGIN

class GuildPatch : public Patch
{
public:
	void setName(const QString& name);
	void setRegion(const QString& region);
	void setIcon(const QString& icon);
	void setSplash(const QString& splash);

	void setAfkChannelId(snowflake_t afk_channel_id);
	void setOwnerId(snowflake_t owner_id);
	void setSystemChannelId(snowflake_t system_channel_id);

	void setVerificationLevel(int verification_level);
	void setDefaultMessageNotifications(int default_message_notifications);
	void setExplicitContentFilter(int explicit_content_filter);
	void setAfkTimeout(int afk_timeout);
};

QDISCORD_NAMESPACE_END
