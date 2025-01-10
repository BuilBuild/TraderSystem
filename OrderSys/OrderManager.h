/*
 * @Author: LeiJiulong
 * @Date: 2025-01-10 17:27:51
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-10 20:36:25
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Context.hpp"

#include <zmq.hpp>
#include <tbb/concurrent_queue.h>
#include <thread>


using OrderQueueGet = tbb::concurrent_bounded_queue<Order>;

class OMS : noncopyable
{
public:
    explicit OMS();
    ~OMS();
    
    /**
     * @brief 用于处理接收到的消息，反序列化收到的订单队列
     */
    void receiveOrderData();
    
    void stop();
private:
    /**
     * @brief 将验证好的订单和失败的订单分别推送到不同的队列
     */
    void pushOrder(Order &);

    /**
     * @brief 用于验证订单是否可以执行
     * @return true 
     * @return false 
     */
    bool orderValidOk(Order &);
    
private:
    // zero 上下文对象
    zmq::context_t zmqContext_;
    // zero 订阅
    zmq::socket_t subscriber_;
    // 收到的订单队列
    OrderQueueGet orderUpdates_;
    // 已经验证好的队列
    OrderQueueGet orderFilledQueue_;
    // 验证失败的队列
    OrderQueueGet OrderFailedQueue_;
    // 接收接收到的订单
    std::thread threadReceiveMsg_;
    // 配置文件上下文对象
    Context *context_;
    // 启动标志
    bool isStop_;
};
