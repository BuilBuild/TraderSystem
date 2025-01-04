/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:29:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 22:38:08
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Strategy.h"

#include <string>
#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_unordered_set.h>
#include <tbb/concurrent_unordered_map.h>

class Strategy;

class QuoteElement
{
    using QuoterSet = tbb::concurrent_unordered_set<Strategy*>;
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

    std::string name() const;

private:
    // 订阅标的的名字
    std::string name_;
    // 订单簿
    OrderBook orderBook_;
    // 被订阅的策略列表
    QuoterSet quoterSet_;
};


using QuoteSet = tbb::concurrent_set<TargetOBJ>;
/**
 * @brief 封装CTP等各种协议
 */
class DataApi : noncopyable
{
    using QuoteElementMap = tbb::concurrent_unordered_map<std::string, QuoteElement>;
public:
    explicit DataApi();
    /**
     * @brief Set the Strategy object 给数据api注册策略
     */
    void setStrategy(Strategy*);

    /**
     * @brief 注册策略和其订阅，当对应的标的有数据更新时，将数据推送到对应的策略里
     * 
     * @param s 
     * @param targetOBJ 
     */
    void subscribeTarget(Strategy *s, const TargetOBJ &targetOBJ);

    /**
     * @brief 删除的策略
     * 
     * @param strategyName 
     */
    void delStrategy(std::string strategyName);

    /**
     * @brief Get the Target Object Quote Set object
     * 返回所有可订阅合集
     */
    const QuoteSet& getTargetObjectQuoteSet();
    
    
private:
    // 全部订阅的列表,k:标的名称，v:订单簿
    QuoteElementMap quoteElementMap_;
    // 可订阅合集
    QuoteSet dataApiTargetObjects_;
};