/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:29:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 02:07:45
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Strategy.h"
#include "SpinLock.hpp"
#include "APIBase.h"

#include <string>
#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_unordered_set.h>
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_queue.h>

#include <thread>
#include <chrono>
#include <mutex>
#include <unordered_map>

class Strategy;

/**
 * @brief 里面维护着一个标的的OrderBook,还有订阅该标的的策略指针，OrderBook更新的时候
 * 回通过策略的指针将数据推送到策略订阅数据的缓存队列，让策略线程处理分发过来的数据
 */
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
    /**
     * @brief 获取该对象的名字，也就是所订阅数据的名称
     */
    std::string name() const;

private:
    // 订阅标的的名字
    std::string name_;
    // 订单簿
    OrderBook orderBook_;
    // 被订阅的策略列表
    QuoterSet quoterSet_;
    std::mutex orderBookUpdateMtx_;
    SpinLock orderBookSpinLock_;
};


using QuoteSet = tbb::concurrent_set<TargetOBJ>;
/**
 * @brief 封装CTP等各种协议
 */
class DataApi : noncopyable
{
    using OrderQueue = tbb::concurrent_queue<OrderBook>;
    using QuoteElementMap = tbb::concurrent_unordered_map<std::string, QuoteElement>;
    // using QuoteElementMap = std::unordered_map<std::string, QuoteElement>;
public:
    explicit DataApi(APIBase *apiBase);
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

    /**
     * @brief 推送订单簿给内部的队列
     * 
     * @param orderBook 
     */
    void PutOrderBook(const OrderBook& orderBook);

    /**
     * @brief 用于分发订单簿的更新到全部订阅列表
     */
    void OrderDistribute();
    
    
private:
    // 全部订阅的列表,k:标的名称，v:订单簿
    QuoteElementMap quoteElementMap_;
    // 可订阅合集
    QuoteSet dataApiTargetObjects_;
    // 推送订单簿的缓冲队列
    OrderQueue orderQueue_;
    // 分发订单簿线程 后期可以用线程池来提高效率
    std::thread threadDistribute_;
    std::thread threadDataGet_;
    // 数据接收源
    APIBase* apiBase_;

};