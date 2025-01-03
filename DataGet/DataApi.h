/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:29:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 00:22:29
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Strategy.h"

#include <string>
#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_unordered_map.h>

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

/**
 * @brief 封装CTP等各种协议
 */
class DataApi
{
    using QuoteElementMap = tbb::concurrent_unordered_map<std::string, QuoteElement>;
public:
    DataApi();
    /**
     * @brief Set the Strategy object 给数据api注册策略
     * 
     */
    void setStrategy(Strategy*);
    void delStrategy(std::string strategyName);
    
private:
    // 全部订阅的列表,k:标的，v:订单簿
    QuoteElementMap QuoteElementMap_;

};