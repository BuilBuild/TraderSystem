/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:27:04
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 16:35:40
 * @Description: 
 */
#include "DataCenter.h"
#include <muduo/base/Logging.h>

std::once_flag DataCenter::singleFlag_;
DataCenter* DataCenter::instance_ = nullptr;

DataCenter *DataCenter::getInstance()
{
    std::call_once(singleFlag_, DataCenter::Construct);
    return instance_;
}

DataCenter::DataCenter()
{
    dataApi_ = DATA_API;
}

DataCenter::~DataCenter()
{
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
