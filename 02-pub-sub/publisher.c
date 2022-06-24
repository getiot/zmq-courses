#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "zmq_helper.h"


int main(void)
{
    void * context = zmq_ctx_new();
    void * socket = zmq_socket(context, ZMQ_PUB);
    zmq_bind(socket, "tcp://*:5556");

    srandom((unsigned)time(NULL));

    while(1)
    {
        int zipcode = randof(1000);   // 邮编: 0 ~ 999
        int temp = randof(84) - 42;     // 温度: -42 ~ 41
        int relhumidity = randof(50) + 10;  // 相对湿度: 10 ~ 59

        char msg[20];
        snprintf(msg, sizeof(msg), "%3d %d %d", zipcode, temp, relhumidity);
        printf("Pub: %s\n", msg);
        
        s_send(socket, msg);

        usleep(1000);
    }

    zmq_close(socket);
    zmq_ctx_destroy(context);

    return 0;

}