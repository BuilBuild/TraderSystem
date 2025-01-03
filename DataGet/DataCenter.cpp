/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:27:04
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 00:23:12
 * @Description: 
 */
#include "DataCenter.h"

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
    dataApi_->setStrategy(s);
}
