#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

/*
 * 把字符串作为字节数据, 发送至zmq socket, 但不发送字符串末尾的'\0'字节
 * 发送成功时, 返回发送的字节数
 */
static inline int s_send(void * socket, const char * string)
{
    return zmq_send(socket, string, strlen(string), 0);
}

/*
 * 从zmq socket中接收数据, 并将其解释为C风格字符串
 * 注意: 该函数返回的字符串是为在堆区创建的字符串
 * 请在使用结束后手动调用free将其释放
 */
static inline char * s_recv(void * socket)
{
    char buffer[256];
    int length = zmq_recv(socket, buffer, 255, 0);
    if(length == -1)
    {
        return NULL;
    }

    buffer[length] = '\0';

    return strndup(buffer, sizeof(buffer) - 1);
}

/*
 * 生成一个位于 [0, num)区间的随机数
 */
#define randof(num) (int)((float)(num) * random() / (RAND_MAX + 1.0))

