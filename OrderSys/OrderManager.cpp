/*
 * @Author: LeiJiulong
 * @Date: 2025-01-10 17:27:51
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-11 18:12:34
 * @Description: 
 */


#include "OrderManager.h"
#include <iostream>
#include <chrono>

OMS::OMS()
    : zmqContext_(1),subscriber_(zmqContext_, ZMQ_SUB),isStop_(false)
{
    context_ = Context::getInstance(); 
    auto t = context_->getJson();
    std::string subAddr = t["OMS"]["SubAddr"];
    std::cout << t["OMS"]["SubAddr"] << std::endl;
    subscriber_.connect(subAddr.c_str());
    subscriber_.setsockopt(ZMQ_SUBSCRIBE, "OMS", 0);
    threadReceiveMsg_ = std::thread(&OMS::receiveOrderData, this);
    
}

OMS::~OMS()
{
    isStop_ = true;
    if(threadReceiveMsg_.joinable())
    {
        threadReceiveMsg_.join();
    }
}

void OMS::receiveOrderData()
{
    while(!isStop_)
    {
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        // std::cout << "receiveOrder" << std::endl;
        zmq::message_t message;
        auto flag = subscriber_.recv(message, zmq::recv_flags::none);
        // std::cout << flag << std::endl;
        std::string update_str(static_cast<char*>(message.data()), message.size());
        std::cout << update_str << std::endl;
        // subscriber_.acc
    }
}

void OMS::stop()
{
    isStop_ = false;
}

void OMS::pushOrder(Order &)
{
}

bool OMS::orderValidOk(Order &)
{
    return false;
}
