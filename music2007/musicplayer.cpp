#include "musicplayer.h"

MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent){
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    player->setVolume(100);
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(newstate(QMediaPlayer::State)));
}

void MusicPlayer::updatelist(MusicList list){
    qDebug() << "Music list updated";
    playlist->clear();
    foreach (MusicItem item, list) {
        playlist->addMedia(QUrl::fromLocalFile(item.path));
    }
}

void MusicPlayer::playpause(int index)
{
    if(index!=playlist->currentIndex())playlist->setCurrentIndex(index);

    if(state==1) player->pause();
    else player->play();

}

void MusicPlayer::next()
{
    qDebug() << "next";
    playlist->next();
    player->pause();
    player->play();
}

void MusicPlayer::prev()
{
    playlist->previous();
    player->pause();
    player->play();
}

void MusicPlayer::newstate(QMediaPlayer::State state)
{
    if(state==QMediaPlayer::StoppedState){
        playlist->setCurrentIndex(0);
        player->play();
    }
    if(state==QMediaPlayer::PlayingState) this->state=1;
    else this->state=0;
}
