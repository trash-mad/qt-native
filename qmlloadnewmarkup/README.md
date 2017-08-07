# qmlloadnewmarkup
QMetaObject::invokeMethod example, you can use it if you want to call QQuickView->setSource(); from your C++ backend to load new qml markup file

If you want to load a new markup file you need to do this in new thread, or your programm will fail
