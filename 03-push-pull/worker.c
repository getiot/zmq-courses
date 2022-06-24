#include <zmq.h>
#include <stdio.h>
#include "zmq_helper.h"

int main(void)
{
    void * context = zmq_ctx_new();
    void * socket_to_ventilator = zmq_socket(context, ZMQ_PULL);
    void * socket_to_sink = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(socket_to_ventilator, "tcp://localhost:5557");
    zmq_connect(socket_to_sink, "tcp://localhost:5558");

    while(1)
    {
        char * msg = s_recv(socket_to_ventilator);
        printf("Received msg: %s\n", msg);
        fflush(stdout);
        s_sleep(atoi(msg));     // 干活, 即睡眠指定毫秒
        free(msg);
        s_send(socket_to_sink, "DONE"); // 活干完了通知监理
    }

    zmq_close(socket_to_ventilator);
    zmq_close(socket_to_sink);
    zmq_ctx_destroy(context);

    return 0;
}