/**
 * @author luobingyong
 * @date 2020/9/8
 */
#include <jni.h>
#include <stdlib.h>
#include<android/log.h>
#include <string.h>

static const char *TAG = "hid_transport";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)

JNIEXPORT jstring JNICALL
Java_com_itkluo_ndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject jobj) {
    //JNIEnv 结构体指针
    //env二级指针(对应c，在C++是一个结构体的一级指针)，由于需要用到JNIEnv变量，而JNIEnv是结构体指针，需要一个变量来表示JNIEnv，所以这个变量就是二级指针，而C++中有this关键字的，直接可以表示
    //每个native函数，都至少有两个参数(JNIEnv*，jclass或者jobject)
    //1.当native方法为静态方法时，jclass代表native方法所属类的class对象(MainActivity.class)
    //2.当native方法为非静态方法时，jobject代表native方法所属类的对象
    LOGD("print file %s", "ha ha");
    return (*env)->NewStringUTF(env, "Welcome to JNI");
}

//C/C++访问Java的成员
//访问非静态属性
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_accessField(JNIEnv *env, jobject jobj) {
    //得到jclass
    jclass jcla = (*env)->GetObjectClass(env, jobj);
    //得到jfieldID，最后一个参数是签名，String对应的签名是Ljava/lang/String;(注意最后的分号)
    jfieldID  jfID = (*env)->GetFieldID(env, jcla, "key", "Ljava/lang/String;");
    //得到key属性的值jstring
    jstring jstr = (*env)->GetObjectField(env, jobj, jfID);
    //jstring转化为C中的char*
    const char* oriText = (*env)->GetStringUTFChars(env, jstr, NULL);
    //拼接得到新的字符串text="China John"
    char text[20] = "China ";
    strcat(text, oriText);
    //C中的char*转化为JNI中的jstring
    jstring jstrMod = (*env)->NewStringUTF(env, text);
    //修改key
    (*env)->SetObjectField(env, jobj, jfID, jstrMod);
    //只要使用了 GetStringUTFChars，就需要释放
    (*env)->ReleaseStringUTFChars(env, jstr, oriText);
}

//访问静态属性
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_accessStaticField(JNIEnv *env, jobject jobj) {
    //得到jclass
    jclass jcla = (*env)->GetObjectClass(env, jobj);
    //得到jfieldID
    jfieldID jfid = (*env)->GetStaticFieldID(env, jcla, "count", "I");
    //得到静态属性的值count
    jint count = (*env)->GetStaticIntField(env, jcla, jfid);
    //自增
    count++;
    //修改count的值
    (*env)->SetStaticIntField(env, jcla, jfid, count);
}