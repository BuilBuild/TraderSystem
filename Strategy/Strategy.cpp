/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:02:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 19:37:10
 * @Description: 
 */
#include "Strategy.h"
#include "DataCenter.h"

Strategy::Strategy(std::string nameArg, DataCenter *dataCenter)
    :name_(nameArg),dataCenter_(dataCenter)
{
    dataCenter_->setStrategy(this);
}

void Strategy::pushDate(const OrderBook &)
{
}

void Strategy::subScribeTargets(const TargetOBJ targetObjects[], size_t num)
{
    for(int i = 0; i<num; ++i)
    {
        subscribeSet_.insert(targetObjects[i]);
    }
    dataCenter_->updateSubscribe(this);
}

void Strategy::subScribeTargetOne(const TargetOBJ &oneTargetObject)
{
    subscribeSet_.insert(oneTargetObject);
    dataCenter_->updateSubscribe(this);
}

std::string Strategy::name() const
{
    return name_;
}

const TargetSubscribeSet& Strategy::targetSubscribe() const
{
    return subscribeSet_;
}
