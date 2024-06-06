#pragma once
#include <QString>

class Song {
public:
    Song(const QString& title, const QString& artist, const QString& duration, const QString& mediaPath)
        : title(title), artist(artist), duration(duration), mediaPath(mediaPath) {}

    QString getTitle() const { return title; }
    QString getArtist() const { return artist; }
    QString getDuration() const { return duration; }
    QString getMediaPath() const { return mediaPath; }

private:
    QString title;
    QString artist;
    QString duration;
    QString mediaPath;
};
