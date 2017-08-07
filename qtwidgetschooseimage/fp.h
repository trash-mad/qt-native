#ifndef FP_H
#define FP_H

#include <QAndroidActivityResultReceiver>

class MainWindow;

class FP : public QAndroidActivityResultReceiver
{
public:
FP();
MainWindow *parent;

private:
void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data);

};

#endif // FP_H
