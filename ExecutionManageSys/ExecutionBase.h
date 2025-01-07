/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 17:22:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 19:04:24
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"

#include <tbb/concurrent_queue.h>

using OrderExecuteQueue = tbb::concurrent_bounded_queue<InputOrderField>;

class ExecutionBase : noncopyable
{
public:
    ExecutionBase();
    virtual ~ExecutionBase(){}

    /**
     * @brief 订单插入
     * 
     * @param inputOrderField 
     */
    virtual void orderInsert(InputOrderField& inputOrderField)
    {
        orderExecuteQueue_.emplace(inputOrderField);
    }
    virtual void onOrderInsert() = 0;
    virtual void onOrderExecute() = 0;
    /**
     * @brief 读取配置文件并初始化
     */
    virtual void init() = 0;
protected:
    OrderExecuteQueue orderExecuteQueue_;
    
};
