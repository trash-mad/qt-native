package com.example.getimage.fetch;

/*import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.ParcelFileDescriptor;
import android.os.Bundle;
import java.io.File;
import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;*/
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.database.Cursor;
import android.provider.MediaStore;
import android.graphics.Bitmap;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.File;
import static java.util.UUID.randomUUID;




public class FetchClass extends org.qtproject.qt5.android.bindings.QtActivity
{

    public static Intent createChooseImageIntent() {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("image/*");
        return intent;
     }


     public static String getFilePath(Context context, Uri uri) throws IOException {
         Bitmap bitmap = MediaStore.Images.Media.getBitmap(context.getContentResolver(),uri);

         String file_path = context.getApplicationInfo().dataDir;
         File dir = new File(file_path);
         File file = new File(dir, randomUUID()+".png");
         FileOutputStream fOut = null;
         try {
             fOut = new FileOutputStream(file);
         } catch (FileNotFoundException e) {
             e.printStackTrace();
         }
         bitmap.compress(Bitmap.CompressFormat.PNG, 85, fOut);
         fOut.flush();
         fOut.close();

         return file.toString();
     }



}
