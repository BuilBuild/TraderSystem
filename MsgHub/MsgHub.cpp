/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 15:36:36
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 16:21:17
 * @Description: 
 */
#include "MsgHub.h"

MessagingHub::MessagingHub()
    :context_(1), publisher_(context_, ZMQ_PUB)
{
    publisher_.bind(
        Context::getInstance()->messageHubBindPort().c_str());
    std::cout << "after bind" << std::endl;
    runThread_ = std::thread([this]{
        this->run();
    } 
    );
}

void MessagingHub::run()
{
    // 将线程绑定到某个CPU核心上
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "1" << std::endl;
        std::string msg_send = "msg hub pull";
        zmq::message_t msg(msg_send.size());
        memcpy(msg.data(), msg_send.data(), msg_send.size());
        publisher_.send(msg);
    }

}
