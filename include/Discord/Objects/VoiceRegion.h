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

class VoiceRegion
{
public:
	explicit VoiceRegion(const QJsonObject& data);

	operator QJsonObject() const;

	const QString& id() const { return id_; }
	const QString& name() const { return name_; }
	const QString& sampleHostname() const { return sample_hostname_; }

	int samplePort() const { return sample_port_; }

	bool vip() const { return vip_; }
	bool optimal() const { return optimal_; }
	bool deprecated() const { return deprecated_; }
	bool custom() const { return custom_; }

private:
	QString id_;
	QString name_;
	QString sample_hostname_;

	int sample_port_;

	bool vip_;
	bool optimal_;
	bool deprecated_;
	bool custom_;
};

QDISCORD_NAMESPACE_END
