/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 17:23:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 23:24:51
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "ExecutionBase.h"
#include "Context.hpp"

#include <tbb/concurrent_queue.h>


using OrderQueue = tbb::concurrent_bounded_queue<Order>;

class ExecutionSystem : noncopyable
{
public:
    ExecutionSystem() = delete;
    ExecutionSystem(ExecutionBase *execution);
    ~ExecutionSystem();
    /**
     * @brief 订单插入接口
     * 
     * @param order 
     */
    void orderPut(const Order &order);

    void orderGet();
    
    void getPositionInfo();

    void getTradingInfo();
    

private:
    ExecutionBase *executionBase_;
    // 接收的订单队列
    OrderQueue orderQueue_;
    // 配置文件
    Context* context_;
};