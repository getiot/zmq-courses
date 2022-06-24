#include <zmq.h>
#include <stdio.h>
#include "zmq_helper.h"

int main(void)
{
    void * context = zmq_ctx_new();
    void * socket_to_worker_and_ventilator = zmq_socket(context, ZMQ_PULL);
    zmq_bind(socket_to_worker_and_ventilator, "tcp://*:5558");

    char * msg = s_recv(socket_to_worker_and_ventilator);
    printf("Received msg: %s", msg);    // 接收来自包工头的开始干活的消息
    free(msg);

    int64_t start_time = s_clock();

    for(int i = 0; i < 100; ++i)
    {
        // 接收100个worker干完活的消息
        char * msg = s_recv(socket_to_worker_and_ventilator);
        free(msg);

        if(i / 10 * 10 == i)
            printf(":");
        else
            printf(".");
        fflush(stdout);
    }

    printf("Total elapsed time: %d ms]\n", (int)(s_clock() - start_time));

    zmq_close(socket_to_worker_and_ventilator);
    zmq_ctx_destroy(context);

    return 0;
}