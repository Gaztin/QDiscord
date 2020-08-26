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
#include "Discord/Objects/Overwrite.h"
#include "Discord/Patches/Patch.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

class ChannelPatch : public Patch
{
public:
	void addPermissionOverwrite(const Overwrite& permission_overwrite);
	void setPermissionOverwrites(
		const QList<Overwrite>& permission_overwrites);

	void setName(const QString& name);
	void setTopic(const QString& topic);

	void setParentId(snowflake_t parent_id);

	void setPosition(int position);
	void setBitrate(int bitrate);
	void setUserLimit(int user_limit);

	void setNsfw(bool nsfw);
};

QDISCORD_NAMESPACE_END
