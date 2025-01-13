/*
 * @Author: LeiJiulong
 * @Date: 2025-01-10 17:27:51
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-13 23:42:24
 * @Description: 
 */


#include "OrderManager.h"
#include "json.hpp"

#include <iostream>
#include <chrono>


using json = nlohmann::json;

OMS::OMS(ExecutionSystem *executionSystem)
    : zmqContext_(1),subscriber_(zmqContext_, ZMQ_SUB),isStop_(false),executionSystem_(executionSystem)
{
    context_ = Context::getInstance(); 
    auto t = context_->getJson();
    std::string subAddr = t["OMS"]["SubAddr"];
    std::cout << t["OMS"]["SubAddr"] << std::endl;
    subscriber_.connect(subAddr.c_str());
    subscriber_.setsockopt(ZMQ_SUBSCRIBE, "OMS", 3);

    threadReceiveMsg_ = std::thread(&OMS::receiveOrderData, this);
    threadVerifyOrder_ = std::thread([this]{
        while(true)
        {
            orderVerify();
        }
    });
    threadOrderPutExecution_ = std::thread([this]{
        while(true)
        {
            std::cout << "送入执行订单执行器具" << std::endl;
            Order order;
            // 当队列为空时线程会堵塞这里
            orderFilledQueue_.pop(order);
            executionSystem_->orderPut(order);
        }
    });
}

OMS::~OMS()
{
    isStop_ = true;
    if(threadReceiveMsg_.joinable())
    {
        threadReceiveMsg_.join();
    }
    if(threadVerifyOrder_.joinable())
    {
        threadVerifyOrder_.join();
    }
    if(threadOrderPutExecution_.joinable())
    {
        threadOrderPutExecution_.join();
    }
}

void OMS::receiveOrderData()
{
    while(!isStop_)
    {
        zmq::message_t toPic;
        auto flag = subscriber_.recv(toPic, zmq::recv_flags::none);
        std::string toPicStr(static_cast<char*>(toPic.data()),toPic.size());
        std::cout << "get toPic: " <<toPicStr << std::endl;

        zmq::message_t message;
        flag = subscriber_.recv(message, zmq::recv_flags::none);
        std::string messageStr(static_cast<char*>(message.data()),message.size());
        std::cout << "get message: " << messageStr << std::endl;
        auto orderGet = json::parse(messageStr);
        std::string StrategyName = orderGet["StrategyName"];
        std::string TargetName = orderGet["TargetName"];
        std::string UserName = orderGet["UserName"];
        double Price = orderGet["Price"];
        int Volume = orderGet["Volume"];
        // char Direction = std::string(orderGet["Direction"])[0];

        // 将收到的信息序列化，经过验证后存储到执行订单队列
        Order order{};
        memcpy(order.StrategyName, StrategyName.c_str(), StrategyName.length());
        memcpy(order.TargetName, TargetName.c_str(), TargetName.length());
        memcpy(order.UserName, UserName.c_str(), UserName.length());
        order.Price = Price;
        order.Volume = Volume;
        // order.Direction = Direction;
        
        // 将订单推送入更新队列
        orderUpdates_.emplace(order);
        std::cout << orderUpdates_.size() << std::endl;

    }
}

void OMS::stop()
{
    isStop_ = false;
}

void OMS::pushOrder(const Order & order)
{
    executionSystem_->orderPut(order);
}

bool OMS::orderValidOk(Order &)
{

    return true;
}

void OMS::orderVerify()
{
    Order order;
    // 当orderupdate没有订单时会堵塞在这里
    orderUpdates_.pop(order);
    if(orderValidOk(order))
    {
        orderFilledQueue_.emplace(order);
    }
    else
    {
        OrderFailedQueue_.emplace(order);
    }
}
