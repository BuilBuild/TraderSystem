/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 16:22:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 18:51:42
 * @Description: 
 */
#include "zhelpers.h"
#include "Context.hpp"


#include <zmq.h>
#include <stdio.h>

char CONFIG_PATH[] = "/home/leijiulong/git_project/TraderSystem/ConfigFileDir/config.json";

/**
zmq::context_t context(1);
zmq::socket_t subscriber(context, ZMQ_SUB);
subscriber.connect("tcp://localhost:5555");
subscriber.setsockopt(ZMQ_SUBSCRIBE, "weather", 7);
zmq::message_t received;
subscriber.recv(&received);
std::cout << "Received: " << received.data() << std::endl;
 */

int main(int argc, char* argv[])
{
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    int rc = zmq_connect(subscriber, Context::getInstance()->messageHubBindPort().c_str());
    assert(rc == 0);
    
    // 订阅的主题
    char *filter = "weather";
    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));
    assert(rc == 0);

    int update_nbr;
    long total_temp = 0;
    for(update_nbr = 0; update_nbr< 6; ++update_nbr)
    {
        printf("beging\n");
        char* rec_str = s_recv(subscriber);
        
        printf("get string : %s\n", rec_str);
        free(rec_str);
    }
    zmq_close(subscriber);
    zmq_ctx_destroy(context);

    return 0;
}