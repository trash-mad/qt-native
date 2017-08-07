#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include <QDialog>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QScrollBar>

class GuiWindow : public QObject
{
    Q_OBJECT
    QVBoxLayout *verticalLayout;
    QTextBrowser *textoutput;
    QDialog *Dialog;

public:
    GuiWindow();
    ~GuiWindow();
    void setupUi(QDialog *window);

public slots:
    void addLog(QString log);

};

#endif // GUIWINDOW_H
