/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:02:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 16:14:57
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

std::string Strategy::name() const
{
    return name_;
}
