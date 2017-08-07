# qtwidgetschooseimage
Call choose image intent on android with QWidgets

This example can work only with JPEG images. If you want to use this with PNG you need to change Bitmap.CompressFormat.JPEG to Bitmap.CompressFormat.PNG in Java getBitmapBase64 static function and change QImage::fromData(by, "JPEG"); to QImage::fromData(by, "PNG"); in MainWindow::on_pushButton_clicked() Qt slot
