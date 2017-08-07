#ifndef DROPITEM_H
#define DROPITEM_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QtWidgets>



class QDragEnterEvent;
class QDropEvent;

class DropItem : public QWidget
{
Q_OBJECT

QString path="file:///";
QString name="NONAME";

QVBoxLayout *verticalLayout;
QLabel *label;
QLabel *label_2;

public:
    explicit DropItem(QWidget *parent = 0);
    ~DropItem(){
    this->destroy();
    }

    void setPath(QString path){
        this->path=path;

        label->setPixmap(QPixmap(path).scaled(QSize(64, 64)));

    }

    void setName(QString name){
        this->name=name;
        label_2->setText(name);
    }

private:
    void setupUi(QWidget *Form);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void needupdate();
};

#endif // DROPITEM_H
