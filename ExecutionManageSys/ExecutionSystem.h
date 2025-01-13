/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 17:23:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-13 21:38:13
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "ExecutionBase.h"
#include "Context.hpp"
#include "CTP/ThostFtdcTraderApi.h"

#include <thread>
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
     */
    void orderPut(const Order &order);
    /**
     * @brief 
     */
    void orderGet();
    /**
     * @brief Get the Position Info object 获取持仓信息
     */
    void getPositionInfo();
    /**
     * @brief Get the Trading Info object 获取资金情况
     */
    void getTradingInfo();
    /**
     * @brief 执行订单
     */
    void executeOrder(Order &order);
    

private:
    ExecutionBase *executionBase_;
    // 接收的订单队列
    OrderQueue orderQueue_;
    // 配置文件
    Context* context_;
    // 订单执行线程
    std::thread executeThread_;

};