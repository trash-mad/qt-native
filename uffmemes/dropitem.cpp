#include "dropitem.h"


DropItem::DropItem(QWidget *parent) : QWidget(parent){
    setupUi(this);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

void DropItem::setupUi(QWidget *Form){
       if (Form->objectName().isEmpty())
           Form->setObjectName(QStringLiteral("Form"));
       Form->resize(321, 300);
       verticalLayout = new QVBoxLayout(Form);
       verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
       label = new QLabel(Form);
       label->setObjectName(QStringLiteral("label"));
       QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
       sizePolicy.setHorizontalStretch(0);
       sizePolicy.setVerticalStretch(0);
       sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
       label->setSizePolicy(sizePolicy);

       verticalLayout->addWidget(label);

       label_2 = new QLabel(Form);
       label_2->setObjectName(QStringLiteral("label_2"));
       label_2->setAlignment(Qt::AlignCenter);

       verticalLayout->addWidget(label_2);
}

void DropItem::mousePressEvent(QMouseEvent *event)
{   
    if(event->button() == Qt::LeftButton){
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QByteArray itemData=QByteArray::fromStdString("file:///"+path.replace(" ","%20",Qt::CaseInsensitive).toStdString())+ " " + QVariant(QPoint(event->pos() - child->pos())).toByteArray();

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("text/uri-list", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - child->pos());


    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
    }
    }
    if(event->button() == Qt::RightButton){

        int button = QMessageBox::question(this, "Удалить?", "Вы точно хотите удалить?", QMessageBox::Yes | QMessageBox::No);
            if (button == QMessageBox::Yes) {

               QFile::remove(path);
                emit needupdate();

            }

    }
}
