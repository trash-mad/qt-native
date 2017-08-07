#ifndef MUSICSTORAGE_H
#define MUSICSTORAGE_H

/*
 * Данный класс реализует поиск музыки и выбрасывает сигнал needupdate() если рукозадый че нить потрет или добавит
 * К сигналу следует подключить всё, что требует список mp3 файлов
 * Сканирование каждые 5 секкунд, если изменений нет, то сигнал не выбросится, так что храните копию списка музыки у себя
 * Как параметр дает QList из структуры MusicItem, что позволит оперативно составить списочек
 *
 * Вызвать обновление можно принудительно через слот checkupdate(), но не стоит. Таймер никто не завершал, подождите 5 секкунд
 *
 */


#include <QObject>
#include <QTimer>
#include <QSettings>
struct MusicItem{
    QString name="NAME";
    QString path="PATH";
    int id=0;
};

typedef QList<MusicItem> MusicList;

class MusicStorage : public QObject
{
Q_OBJECT

MusicList itemlist;
QTimer *timer;
unsigned int musiccount=0;

public:
explicit MusicStorage(QObject *parent = 0);
~MusicStorage();

private:
int scannewfiles(QString path);
int scanoldfiles();

signals:
void needupdate(MusicList list); //Вызывается как только есть новый элемент

public slots:
void checkupdate();

};

#endif // MUSICSTORAGE_H
