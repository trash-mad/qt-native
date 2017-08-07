package com.example.qtwidgetschooseimage.fetch;

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
import android.graphics.Bitmap;
import java.io.ByteArrayOutputStream;
import android.util.Base64;




public class FetchClass extends org.qtproject.qt5.android.bindings.QtActivity
{

    public static Intent createChooseImageIntent() {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("image/*");
        return intent;
     }


     public static String getBitmapBase64(Context context, Uri uri) throws IOException {
         Bitmap bitmap = MediaStore.Images.Media.getBitmap(context.getContentResolver(),uri);

         ByteArrayOutputStream byteArrayOS = new ByteArrayOutputStream();
         bitmap.compress(Bitmap.CompressFormat.JPEG, 10, byteArrayOS);
         return Base64.encodeToString(byteArrayOS.toByteArray(), Base64.DEFAULT);
     }



}
