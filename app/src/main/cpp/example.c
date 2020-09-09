/**
 * @author luobingyong
 * @date 2020/9/8
 */
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <android/log.h>
#include <stdlib.h>
#include<stdarg.h>
#include <jni.h>

static const char *TAG = "example";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)

JNIEXPORT jstring JNICALL
Java_com_itkluo_ndk_MainActivity_getStringFromJNI(
        JNIEnv *env,
        jobject thiz) {
    //JNIEnv 结构体指针
    //env二级指针(对应c，在C++是一个结构体的一级指针)，由于需要用到JNIEnv变量，而JNIEnv是结构体指针，需要一个变量来表示JNIEnv，所以这个变量就是二级指针，而C++中有this关键字的，直接可以表示
    //每个native函数，都至少有两个参数(JNIEnv*，jclass或者jobject)
    //1.当native方法为静态方法时，jclass代表native方法所属类的class对象(MainActivity.class)
    //2.当native方法为非静态方法时，jobject代表native方法所属类的对象
    LOGD("print file %s", "ha ha");
    return (*env)->NewStringUTF(env, "Welcome to JNI");
}
//JNI基本数据类型
//Java基本数据类型与JNI
//Java类型<-->JNI类型<-->C类型

//基本数据类型
/*
boolean     jboolean;
byte        jbyte;
char        jchar;
short       jshort;
int         jint;
long        jlong;
float       jfloat;
double      jdouble;
void        void
*/

//引用类型(对象)
/*
    String                  jstring
    Object                  jobject
//基本数据类型的数组
    byte[]               jByteArray
//对象数组
Object[](String[])      jobjectArray
*/


//C/C++访问Java的成员
//访问非静态属性
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_accessField(JNIEnv *env, jobject thiz) {
    //得到jclass
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    //得到jfieldID，最后一个参数是签名，String对应的签名是Ljava/lang/String;(注意最后的分号)
    jfieldID jfID = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String;");
    //得到key属性的值jstring
    jstring jstr = (*env)->GetObjectField(env, thiz, jfID);
    //jstring转化为C中的char*
    const char *oriText = (*env)->GetStringUTFChars(env, jstr, NULL);
    //拼接得到新的字符串text="China John"
    char text[20] = "China ";
    strcat(text, oriText);
    //C中的char*转化为JNI中的jstring
    jstring jstrMod = (*env)->NewStringUTF(env, text);
    //修改key
    (*env)->SetObjectField(env, thiz, jfID, jstrMod);
    //只要使用了 GetStringUTFChars，就需要释放
    (*env)->ReleaseStringUTFChars(env, jstr, oriText);
}

//访问静态属性
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_accessStaticField(JNIEnv *env, jobject thiz) {
    //得到jclass
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    //得到jfieldID
    jfieldID jfid = (*env)->GetStaticFieldID(env, clazz, "count", "I");
    //得到静态属性的值count
    jint count = (*env)->GetStaticIntField(env, clazz, jfid);
    //自增
    count++;
    //修改count的值
    (*env)->SetStaticIntField(env, clazz, jfid, count);
}

//访问Java非静态方法
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_accessMethod(JNIEnv *env, jobject thiz) {
    //得到jclass
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    //得到jmethodID
    jmethodID jmid = (*env)->GetMethodID(env, clazz, "getRandomInt", "(I)I");
    //调用java方法获取返回值，第四个参数100表示传入到java方法中的值
    jint jRandom = (*env)->CallIntMethod(env, thiz, jmid, 100);
    //可以在Android Studio中Logcat显示，需要定义头文件#include <android/log.h>
    __android_log_print(ANDROID_LOG_DEBUG, "system.out", "Random：%d", jRandom);
}

//访问Java中静态方法
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_accessStaticMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jmethodID jmid = (*env)->GetStaticMethodID(env, clazz, "getUUID", "()Ljava/lang/String;");
    jstring uuid = (*env)->CallStaticObjectMethod(env, clazz, jmid);
    const char *uuid_str = (*env)->GetStringUTFChars(env, uuid, NULL);
    __android_log_print(ANDROID_LOG_DEBUG, "system.out", "uuid_str：%ld", uuid_str);
}

//访问Java中构造方法
//实现访问Java中的Date构造方法，实例化Date对象，再利用这个对象调用getTime产生一个时间戳，并打印其值。
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_accessConstructor(JNIEnv *env, jobject thiz) {
    //得到类Date对应的jclass
    jclass clazz = (*env)->FindClass(env, "java/util/Date");
    //构造方法对应的都是<init>
    //在任意位置打开命令行，输入javap -s -p java.util.Date可以看到空参构造的签名是()V
    jmethodID jmid = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    //实例化Date对象
    jobject jDate = (*env)->NewObject(env, clazz, jmid);
    //下面需要调用的是getTime，对应这里第三个参数传入getTime，第四个参数为其签名
    jmethodID jTimeMid = (*env)->GetMethodID(env, clazz, "getTime", "()J");
    //调用getTime方法得到返回值jlong
    jlong jtime = (*env)->CallLongMethod(env, jDate, jTimeMid);

    __android_log_print(ANDROID_LOG_DEBUG, "system.out", "jtime：%ld", jtime);
}

//调用父类的方法
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_accessNonvirtualMethod(JNIEnv *env, jobject thiz) {
    //得到MainActivity对应的jclass
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    //得到animal属性对应的jfieldID
    jfieldID jfid = (*env)->GetFieldID(env, clazz, "animal",
                                       "Lcom/itkluo/ndk/Animal;");   //这里必须是父类对象的签名，否则会报NoSuchFieldError，因为Java中是父类引用指向子类对象
    //得到animal属性对应的jobject
    jobject animalObj = (*env)->GetObjectField(env, thiz, jfid);
//    jclass animalCla =(*env)->GetObjectClass(env, animalObj); //这种方式，下面调用CallNonvirtualVoidMethod会执行子类的方法
    //找到Animal对应的jclass
    jclass animalCla = (*env)->FindClass(env,
                                         "com/itkluo/ndk/Animal");   //如果这里写成子类的全类名，下面调用CallNonvirtualVoidMethod会执行子类的方法
    //得到eat对应的jmethodID
    jmethodID eatID = (*env)->GetMethodID(env, animalCla, "eat", "()V");
//    (*env)->CallVoidMethod(env, animalCla, eatID);      //这样调用会报错
    //调用父类的方法
    (*env)->CallNonvirtualVoidMethod(env, animalObj, animalCla, eatID);     //输出父类的方法
}

int commpare(int *a, int *b) {
    return (*a) - (*b);
}

//传入数组
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_putArray(JNIEnv *env, jobject thiz, jintArray arr_) {
    //jintArray --> jint指针 --> C int 数组
    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);
    //数组的长度
    jint arrLength = (*env)->GetArrayLength(env, arr_);
    //排序
    qsort(arr, arrLength, sizeof(jint), commpare);

    //同步
    //0：Java数组进行更新，并且释放C/C++数组
    //JNI_ABORT：Java数组不进行更新，但是释放C/C++数组
    //JNI_COMMIT：Java数组进行更新，不释放C/C++数组(函数执行完后，数组还是会释放的)
    (*env)->ReleaseIntArrayElements(env, arr_, arr, JNI_COMMIT);
}

//返回数组
JNIEXPORT jintArray JNICALL
Java_com_itkluo_ndk_MainActivity_getArray(JNIEnv *env, jobject thiz, jint arrLength) {
    //创建一个指定大小的数组
    jintArray  array = (*env)->NewIntArray(env, arrLength);
    jint* elementp = (*env)->GetIntArrayElements(env, array, NULL);
    jint* startP = elementp;
    int i = 0;
    for (; startP < elementp + arrLength; startP++) {
        (*startP) = i;
        i++;
    }
    //同步，如果没有同步Java层打印出来的数组里面的各个值为0
    (*env)->ReleaseIntArrayElements(env, array, elementp, 0);
    return array;
}

//JNI 引用变量
//引用类型：局部引用和全局引用
//作用：在JNI中告知虚拟机何时回收一个JNI变量

//局部引用，通过DeleteLocalRef手动释放对象
//1.访问一个很大的java对象，使用完之后，还要进行复杂的耗时操作
//2.创建了大量的局部引用，占用了太多的内存，而且这些局部引用跟后面的操作没有关联性

//模拟：循环创建数组
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_localRef(JNIEnv *env, jobject thiz) {
    int i = 0;
    for (; i < 5; i++) {
        //创建Date对象
        jclass  clazz = (*env)->FindClass(env, "java/util/Date");
        jmethodID  jmid = (*env)->GetMethodID(env, clazz, "<init>", "()V");
        jobject thiz = (*env)->NewObject(env, clazz, jmid);
        //此处省略一百行代码...

        //不再使用jobj对象了
        //通知垃圾回收期回收这些对象
        (*env)->DeleteLocalRef(env, thiz);

        //此处省略一百行代码...
    }
}

//全局引用
//共享(可以跨多个线程)，手动控制内存使用

//创建
jstring jstr;
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_createGlobalRef(JNIEnv *env, jobject thiz) {
    jstring obj = (*env)->NewStringUTF(env, "China is Powerful");
    jstr = (*env)->NewGlobalRef(env, obj);
}

//获得
JNIEXPORT jstring JNICALL
Java_com_itkluo_ndk_MainActivity_getGlobalRef(JNIEnv *env, jobject thiz) {
    return jstr;
}

//释放
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_deleteGlobalRef(JNIEnv *env, jobject thiz) {
    (*env)->DeleteGlobalRef(env, jstr);
}

//弱全局引用
//节省内存，在内存不足时可以释放所引用的对象
//可以引用一个不常用的对象，如果为NULL（被回收了），可以手动临时创建一个
//创建：NewWeakGlobalRef，销毁：DeleteGlobalWeakRef


//中文问题，eclipse是有中文乱码问题的，但是我用Android Studio就没有中文乱码问题了，还是因为Android Studio版本问题？
JNIEXPORT jstring JNICALL
Java_com_itkluo_ndk_MainActivity_accessChineseChars(JNIEnv *env, jobject instance,
                                                             jstring str_) {
    char* newChar = "宋喆";
    return (*env)->NewStringUTF(env, newChar);
}

//异常处理
//1.保证Java代码可以运行
//2.补救措施保证C代码可以继续运行

//JNI自己抛出的异常，在Java层无法被捕捉，只能在C层清空
//用户通过ThrowNew抛出的异常，可以在Java层捕捉
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_exception(JNIEnv *env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID jfid = (*env)->GetFieldID(env, clazz, "key2", "Ljava/lang/String;");
    //检测是否发生异常
    jthrowable exception = (*env)->ExceptionOccurred(env);
    jboolean isException = (*env)->ExceptionCheck(env);
    if (/*exception != NULL*/isException) {
        //让Java代码可以继续运行
        //清空异常信息
        (*env)->ExceptionClear(env);

        //补救措施
        jfid = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String;");

    }

    //获取属性的值
    jstring jstr = (*env)->GetObjectField(env, thiz, jfid);
    const char* str = (*env)->GetStringUTFChars(env, jstr, NULL);

    //对比属性值是否合法
    if(strcmp(str, "China John1") != 0) {
        //人为抛出异常，给Java层处理
        jclass  newExceCls = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
        (*env)->ThrowNew(env, newExceCls, "key's value is invalid");
    }
}

//缓存策略
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_cache(JNIEnv *env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    //局部静态变量，作用域当然是函数中
    //在第一次调用函数的时候会初始化，函数结束，但是它的值还会存在内存当中（只有当程序结束了才会销毁），只会声明一次
    static jfieldID jfid = NULL;   //如果加了static修饰，下面就只有一个打印，如果没加，for循环执行了多少次就打印多少次，这里是10次
    if (jfid == NULL) {
        jfid = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String;");
        __android_log_print(ANDROID_LOG_DEBUG, "system.out", "---jfieldID---");
    }
}

//初始化全局变量，加载完成之后，立刻缓存
jfieldID globalFID;
jmethodID globalMID;
JNIEXPORT void JNICALL
Java_com_itkluo_ndk_MainActivity_initIDs(JNIEnv *env, jclass clazz) {
    globalFID = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String;");
    globalMID = (*env)->GetMethodID(env, clazz, "getRandomInt", "(I)I");

}
