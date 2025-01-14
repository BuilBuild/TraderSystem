/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 15:36:36
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-14 20:59:39
 * @Description: https://developer.aliyun.com/article/1468023
 */
#include "MsgHub.h"
#include "BaseType.hpp"
#include "json.hpp"

#include <tbb/concurrent_queue.h>
#include <string>

using json = nlohmann::json;

using OrderQueue = tbb::concurrent_bounded_queue<Order>;

MessagingHub::MessagingHub()
    :context_(1), publisher_(context_, ZMQ_PUB)
{
    publisher_.bind(
        Context::getInstance()->messageHubBindPort().c_str());
    
}

void MessagingHub::start()
{
    runThread_ = std::thread([this]{
         // 将线程绑定到某个CPU核心上
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
        
        this->run();
    });
}

void MessagingHub::run()
{   
    double price = 999.2;
    while(true)
    {
        // 用json 模拟一个订单消息
        json orderJson;
        orderJson["StrategyName"] = "test";
        orderJson["UserName"] = "admin";
        orderJson["TargetName"] = "au2502";
        orderJson["Price"] = price;
        orderJson["Volume"] = 2;
        orderJson["Direction"] = "1";
        price += 2.5;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::string topic = "OMS";
        zmq::message_t topicMsg(topic.size());
        memcpy(topicMsg.data(), topic.data(), topic.size());
        publisher_.send(topicMsg, zmq::send_flags::sndmore);

        std::string msg_send =  orderJson.dump();
        zmq::message_t msg(msg_send.size());
        memcpy(msg.data(), msg_send.data(), msg_send.size());
        publisher_.send(msg,zmq::send_flags::none);
    }
}
