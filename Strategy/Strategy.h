/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:20:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 16:20:24
 * @Description: 
 */
#pragma once
#include "BaseType.hpp"

#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_set.h>
#include <string>

class DataCenter;

class Strategy : noncopyable
{
public:
    /**
     * @brief Construct a new Strategy object 
     * 生成一个策略时需要挂载到一个数据中心，数据中心会触发对该策略的注册
     */
    explicit Strategy(std::string, DataCenter *);
    void pushDate(const OrderBook&);

    std::string name() const ;
private:

private:
    std::string name_;
    // 订阅集合
    tbb::concurrent_set<TargetOBJ> subscribeSet_;

    DataCenter* dataCenter_;

};