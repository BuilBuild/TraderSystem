/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:28:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 02:05:49
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
    virtual void onOrderBookReceive(OrderBook &orderBook) = 0;
    virtual void init() = 0;
    virtual void orderBookGet(OrderBook &orderBook)
    {
        // 将结果放如orderBook中，当没有数据时会堵塞
        orderBookQueue_.pop(orderBook);
    }


    std::vector<std::string> instrumentId_;

protected:
    Context *context_;
    OrderBookQueue orderBookQueue_;
};
