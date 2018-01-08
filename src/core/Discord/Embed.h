#pragma once
#include "Discord.h"

#include <QtCore/QDateTime>
#include <QtCore/QList>
#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct EmbedFooter
{
	QString text;
	QString icon_url;
	QString proxy_icon_url;
};

struct EmbedImage
{
	QString url;
	QString proxy_url;
	int height;
	int width;
};

struct EmbedThumbnail
{
	QString url;
	QString proxy_url;
	int height;
	int width;
};

struct EmbedVideo
{
	QString url;
	int height;
	int width;
};

struct EmbedProvider
{
	QString name;
	QString url;
};

struct EmbedAuthor
{
	QString name;
	QString url;
	QString icon_url;
	QString proxy_icon_url;
};

struct EmbedField
{
	QString name;
	QString value;
	bool display_inline;
};

struct Embed
{
	QList<EmbedField> fields;

	QDateTime timestamp;
	QString title;
	QString type;
	QString description;
	QString url;

	EmbedFooter footer;
	EmbedImage image;
	EmbedThumbnail thumbnail;
	EmbedVideo video;
	EmbedProvider provider;
	EmbedAuthor author;

	int color;
};

QDISCORD_NAMESPACE_END