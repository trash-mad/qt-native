#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "musicstorage.h"

class MusicPlayer : public QObject
{
Q_OBJECT
QMediaPlayer *player;
QMediaPlaylist *playlist;

int state=0; //0-пауза 1-играет

public:
    explicit MusicPlayer(QObject *parent = 0);

signals:

public slots:
    void updatelist(MusicList list);
    void playpause(int index);
    void next();
    void prev();

    void newstate(QMediaPlayer::State state);
};

#endif // MUSICPLAYER_H
