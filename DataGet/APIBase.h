/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:28:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 21:29:28
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Context.hpp"

#include <muduo/base/Logging.h>
#include <tbb/concurrent_queue.h>

using OrderBookQueue = tbb::concurrent_bounded_queue<OrderBook>;

class APIBase : noncopyable
{
public:
    explicit APIBase()
    {
        context_ = Context::getInstance();
        LOG_INFO << "APIBase created";
        
    };
    virtual ~APIBase(){};
    virtual void onOrderBookReceive() = 0;
    virtual void init() = 0;

protected:
    OrderBookQueue orderBookQueue_;
    // 配置信息
    Context *context_;
};
