package com.itkluo.api;

import android.util.Log;

/**
 * 本地方法JNI接口
 *
 * @author luobingyong
 * @date 2020/9/8
 */
public class NativeFunc {
    private static final String TAG = "NativeFunc";

    static {
        try {
//            System.loadLibrary("hid_transport");
//            Log.d(TAG, "loadLibrary hid_transport succeed!");
        } catch (Exception e) {
            Log.d(TAG, "static initializer: " + e.toString());
        }
    }




}
