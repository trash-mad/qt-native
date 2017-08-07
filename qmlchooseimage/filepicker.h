#ifndef FILEPICKER_H
#define FILEPICKER_H
#include <QAndroidActivityResultReceiver>
#include <QString>

class BackEnd;

class FilePicker : public QAndroidActivityResultReceiver
{
public:
    FilePicker();
    BackEnd *parent;

private:
    void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data);
};

#endif // FILEPICKER_H
