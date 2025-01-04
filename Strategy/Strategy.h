/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:20:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 19:12:06
 * @Description: 
 */
#pragma once
#include "BaseType.hpp"

#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_set.h>
#include <string>

class DataCenter;

using TargetSubscribeSet =  tbb::concurrent_set<TargetOBJ>;

class Strategy : noncopyable
{
public:
    /**
     * @brief Construct a new Strategy object 
     * 生成一个策略时需要挂载到一个数据中心，数据中心会触发对该策略的注册
     */
    explicit Strategy(std::string, DataCenter *);

    /**
     * @brief 数据推动的接口提供数据，将数据推送到这个接口，相应的策略就可以获取订阅的数据
     */
    void pushDate(const OrderBook&);
    
    /**
     * @brief 订阅标的合集
     * 
     * @param targetObjects 
     * @param num 
     */
    void subScribeTargets(const TargetOBJ targetObjects[], size_t num);
    
    /**
     * @brief 订阅一个标的
     * 
     * @param oneTargetObject 
     */
    void subScribeTargetOne(const TargetOBJ& oneTargetObject);

    /**
     * @brief 获取策略名称
     * 
     * @return std::string 
     */
    std::string name() const ;
    /**
     * @brief 返回所有的订阅的合集
     * 
     * @return const TargetSubscribeSet& 
     */
    const TargetSubscribeSet& targetSubscribe() const;
    
private:

private:
    std::string name_;
    // 订阅集合
    TargetSubscribeSet subscribeSet_;

    DataCenter* dataCenter_;

};