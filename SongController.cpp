#pragma once
#include <QVector>
#include "Song.h"

class SongController {
public:
    void addSong(const Song& song) {
        allSongs.append(song);
    }

    void deleteSong(int index) {
        if (index >= 0 && index < allSongs.size()) {
            allSongs.removeAt(index);
        }
    }

    void addToPlaylist(int index) {
        if (index >= 0 && index < allSongs.size()) {
            playlist.append(allSongs[index]);
        }
    }

    QVector<Song> getAllSongs() const { return allSongs; }
    QVector<Song> getPlaylist() const { return playlist; }

private:
    QVector<Song> allSongs;
    QVector<Song> playlist;
};
