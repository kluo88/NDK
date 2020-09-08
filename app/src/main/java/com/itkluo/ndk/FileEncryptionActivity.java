package com.itkluo.ndk;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.io.File;

/**
 * @author luobingyong
 * @date 2020/9/8
 */
public class FileEncryptionActivity  extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_file_encryption);
    }

    public void mCryption(View view) {
        String normalPath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "Shape@2x.png";
//        String normalPath = "/sdcard/Shape@2x.png";
        String cryptPath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "Shape@2xcrypt.png";
        Encryptor.cryption(normalPath, cryptPath);
        Log.d("zhangpan", "加密完成了...");
    }

    public void mDecryption(View view) {
        String cryptPath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "Shape@2xcrypt.png";
        String decryptPath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "Shape@2xdecrypt.png";
        Encryptor.decryption(cryptPath, decryptPath);
        Log.d("zhangpan", "解密完成了...");
    }
}
