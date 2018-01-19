#include "Activity.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

ActivityTimestamps::ActivityTimestamps(const QJsonObject& data)
	: start_(data["start"].toInt())
	, end_(data["end"].toInt())
{
}

ActivityParty::ActivityParty(const QJsonObject& data)
	: id_(data["id"].toString())
{
	const QJsonArray& party_size_data_array = data["size"].toArray();
	if (party_size_data_array.size() > 0)
		current_size_ = party_size_data_array[0].toInt();
	if (party_size_data_array.size() > 1)
		current_size_ = party_size_data_array[1].toInt();
}

ActivityAssets::ActivityAssets(const QJsonObject& data)
	: large_image_(data["large_image"].toString())
	, large_text_(data["large_text"].toString())
	, small_image_(data["small_image"].toString())
	, small_text_(data["small_text"].toString())
{
}

Activity::Activity(const QJsonObject& data)
	: name_(data["name"].toString())
	, url_(data["url"].toString())
	, details_(data["details"].toString())
	, state_(data["state"].toString())
	, timestamps_(data["timestamps"].toObject())
	, party_(data["party"].toObject())
	, assets_(data["assets"].toObject())
	, type_(static_cast<ActivityType>(data["type"].toInt()))
	, application_id_(data["application_id"].toString().toULongLong())
{
}

QDISCORD_NAMESPACE_END