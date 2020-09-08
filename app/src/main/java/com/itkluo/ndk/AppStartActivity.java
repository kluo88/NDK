package com.itkluo.ndk;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

/**
 * @author luobingyong
 * @date 2020/9/8
 */
public class AppStartActivity extends AppCompatActivity implements View.OnClickListener{
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_app_start);

        initView();
    }

    private void initView() {
        findViewById(R.id.btnBasic).setOnClickListener(this);
        findViewById(R.id.btnEncryptor).setOnClickListener(this);
        findViewById(R.id.btnPatch).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btnBasic:
                startActivity(new Intent(this, MainActivity.class));
                break;
            case R.id.btnEncryptor:
                startActivity(new Intent(this, FileEncryptionActivity.class));
                break;
            case R.id.btnPatch:
                startActivity(new Intent(this, FilePatchActivity.class));
                break;
            default:
                break;
        }
    }
}