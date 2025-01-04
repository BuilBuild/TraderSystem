/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:27:04
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 20:59:10
 * @Description: 
 */
#include "DataCenter.h"
#include <muduo/base/Logging.h>

#include <iostream>

std::once_flag DataCenter::singleFlag_;
DataCenter* DataCenter::instance_ = nullptr;

DataCenter *DataCenter::getInstance()
{
    std::call_once(singleFlag_, DataCenter::Construct);
    return instance_;
}

void DataCenter::updateSubscribe(Strategy* s)
{
    LOG_INFO << s->name() << "  更新订阅";
    // 检查该策略是否被注册到数据中心，若注册过则直接返回，防止被外部调用
    // 也可以用friend方法，用于防止外部调用
    if(checkStrategyIsRegist(s))
    {
        // 策略被注册过，检查策略中的订阅的标的，并将新订阅注册到DataAPI中
        // 遍历策略订阅的标的
        for(const auto &t : s->targetSubscribe())
        {
            // 检查该标的是否是数据中心订阅的数据，若不是订阅中心的数据，则发出警告
            if(TargetObjectQuoteSet_.find(t) != TargetObjectQuoteSet_.end())
            {
                LOG_INFO << "数据中心存在 #####  " << t.name << " 的订阅";
                // 将订阅注册到DataAPI

                
            }
            else
            {
                LOG_INFO << "数据中心不存在 " << t.name << " 的订阅";
            }
        }

    }
    
}

DataCenter::DataCenter()
{
    dataApi_ = DATA_API;
    /*
    从数据dataApi获取可订阅的数据列表，同步至数据中心可订阅列表
    */
   for(const auto &t: dataApi_->getTargetObjectQuoteSet())
   {
        TargetObjectQuoteSet_.insert(t);
   }

}

DataCenter::~DataCenter()
{
}

bool DataCenter::checkStrategyIsRegist(const Strategy *s) const
{
    auto it =  strategyRegistMap_.find(s->name());
    if(it == strategyRegistMap_.end())
    {
        return false;
    }
    return true;
}

void DataCenter::Construct()
{
    instance_ = new DataCenter();
}

void DataCenter::setStrategy(Strategy* s)
{
    auto it = strategyRegistMap_.find(s->name());
    if(it == strategyRegistMap_.end())
    {
        strategyRegistMap_[s->name()] = s;
        dataApi_->setStrategy(s);
    }
    else
    {
        LOG_WARN << s->name() << " 被注册过，请检查该策略相关信息";
    }
}
