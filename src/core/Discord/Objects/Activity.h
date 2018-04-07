#pragma once
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

enum class ActivityType
{
	GAME,
	STREAMING,
	LISTENING,
};

class ActivityTimestamps
{
public:
	explicit ActivityTimestamps(const QJsonObject& data);

	int start() const { return start_; }
	int end() const { return end_; }

private:
	int start_;
	int end_;
};

class ActivityParty
{
public:
	explicit ActivityParty(const QJsonObject& data);

	const QString& id() const { return id_; }

	int currentSize() const { return current_size_; }
	int maxSize() const { return max_size_; }

private:
	QString id_;

	int current_size_;
	int max_size_;
};

class ActivityAssets
{
public:
	explicit ActivityAssets(const QJsonObject& data);

	const QString& largeImage() const { return large_image_; }
	const QString& largeText() const { return large_text_; }
	const QString& smallImage() const { return small_image_; }
	const QString& smallText() const { return small_text_; }

private:
	QString large_image_;
	QString large_text_;
	QString small_image_;
	QString small_text_;
};

class Activity
{
public:
	explicit Activity(const QJsonObject& data);

	const QString& name() const { return name_; }
	const QString& url() const { return url_; }
	const QString& details() const { return details_; }
	const QString& state() const { return state_; }
	
	const ActivityTimestamps& timestamps() const { return timestamps_; }
	const ActivityParty& party() const { return party_; }
	const ActivityAssets& assets() const { return assets_; }
	const ActivityType& type() const { return type_; }
	
	snowflake_t applicationId() const { return application_id_; }

private:
	QString name_;
	QString url_;
	QString details_;
	QString state_;

	ActivityTimestamps timestamps_;
	ActivityParty party_;
	ActivityAssets assets_;
	ActivityType type_;

	snowflake_t application_id_;
};

QDISCORD_NAMESPACE_END