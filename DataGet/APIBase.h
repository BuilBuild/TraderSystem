/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:28:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 19:46:03
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Context.hpp"

#include <tbb/concurrent_queue.h>

using OrderBookQueue = tbb::concurrent_bounded_queue<OrderBook>;

class APIBase : noncopyable
{
public:
    explicit APIBase(){};
    virtual ~APIBase(){};
    virtual void onOrderBookReceive() = 0;
    virtual void init() = 0;

protected:
    OrderBookQueue orderBookQueue_;
};
