/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:29:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 22:59:25
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Strategy.h"

#include <string>
#include <tbb/concurrent_vector.h>

class Strategy;

class QuoteElement
{
    using QuoterList = tbb::concurrent_vector<Strategy*>;
public:

    explicit QuoteElement(std::string nameArg);
    ~QuoteElement();
    
    /**
     * @brief 更新定订单簿 并通知订阅的策略数据更新
     */
    void update(OrderBook&);
    /**
     * @brief 策略订阅
     */
    void subscribe(Strategy*);

private:
    // 订阅标的的名字
    std::string name_;
    // 订单簿
    OrderBook orderBook_;
    // 被订阅的策略列表
    QuoterList quoterList_;
};