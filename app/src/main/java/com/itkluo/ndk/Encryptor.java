package com.itkluo.ndk;

/**
 * @author luobingyong
 * @date 2020/9/8
 */
public class Encryptor {
    static {
        System.loadLibrary("file_encryption");
    }

    //加密
    public native static void cryption(String normalPath, String cryptPath);

    //解密
    public native static void decryption(String cryptPath, String decryptPath);
}
