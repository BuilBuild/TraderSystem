/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 21:51:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 14:44:18
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Strategy.h"
#include "DataApi.h"

#include <string>
// #include <spdlog/spdlog.h>
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_unordered_set.h>
#include <tbb/concurrent_vector.h>
#include <mutex>

// 需要外部实例化一个数据API, 如包装了CTP接口的API
extern DataApi* DATA_API;

/**
 * @brief 单例
 */
class DataCenter
{
    using QuoteSet = tbb::concurrent_set<TargetOBJ>;
    using StrategyRegistMap  = tbb::concurrent_unordered_map<std::string, Strategy*>;
public:
    static DataCenter* getInstance();

    /**
     * @brief Set the Strategy object 注册策略
     */
    void setStrategy(Strategy*);
    /**
     * @brief 更新标定订阅
     */
    void updateSubscribe(Strategy* s);
private:
    DataCenter();
    ~DataCenter();
    
    /**
     * @brief 用于检查策略是否被注册过，通过策略名来检查
     * 
     * @param s 
     * @return true 注册过
     * @return false 没注册过
     */
    bool checkStrategyIsRegist(const Strategy *s) const;

    /**
     * @brief 用于单例初始化构造
     */
    static void Construct();
private:
    // 用于初始化单列对象
    static std::once_flag singleFlag_;
    // 单列对象的指针
    static DataCenter* instance_;
    // 封装好的数据接口
    DataApi* dataApi_;
    // 订阅列表
    QuoteSet TargetObjectQuoteSet_;
    // 数据中心注册的策略集合  
    StrategyRegistMap strategyRegistMap_;
    
};