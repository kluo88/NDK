/**
 * 创建线程与线程结束：
 *
 * <p>
 * POSIX线程
 * https://www.jianshu.com/p/329677b9eaeb
 * </p>
 *
 * @author luobingyong
 * @date 2020/9/9
 */
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


void *thr_fun(void *arg) {
    char *no = (char *) arg;
    int i = 0;

    for (; i < 10; i++) {
        printf("thread:%s,i:%d\n", no, i);
        if (i == 5) {
            //线程结束（自杀）
            pthread_exit((void *) 2);

        }

    }
    return (void *) 1;
}


void main() {
    printf("man thread\n");
    //线程的id
    pthread_t tid;
    //第二个参数表示属性，NULL表示默认属性
    //thr_fun，线程创建之后执行的函数
    pthread_create(&tid, NULL, thr_fun, "1");
    void *retval;
    //等待tid线程结束
    //thr_fun与pthread_exit退出时的参数，都作为第二个参数的内容
    pthread_join(tid, &retval);
    printf("retval：%d\n", (int) retval);

}
