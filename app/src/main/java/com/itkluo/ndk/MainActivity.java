package com.itkluo.ndk;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    public String key = "john";
    private static int count = 10;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("hid_transport");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        System.out.println("修改前：" + key);
        this.accessField();
        System.out.println("修改后：" + key);

        System.out.println("修改前count：" + count);
        accessStaticField();
        System.out.println("修改后count：" + count);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    //访问属性
    public native void accessField();
    //访问静态属性
    public native void accessStaticField();
}
