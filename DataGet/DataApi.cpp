/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:41:44
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 20:49:16
 * @Description: 
 */
#include "DataApi.h"
#include <muduo/base/Logging.h>
#include <iostream>

QuoteElement::QuoteElement(std::string nameArg): name_(nameArg)
{
}

QuoteElement::~QuoteElement()
{
}

void QuoteElement::update(OrderBook &orderBook)
{
    for(auto ele : quoterList_)
    {
        ele->pushDate(orderBook);
    }
}

void QuoteElement::subscribe(Strategy *s)
{
    quoterList_.push_back(s);
}


DataApi::DataApi()
{
    // 模拟一份可订阅合集，后期需从其他地方读入
    for(int i = 0; i< 10; ++i)
    {
        char t_name[128] = {0};
        sprintf(t_name, "target_%d", i);
        TargetOBJ e;
        e.name = t_name;
        dataApiTargetObjects_.insert(e);
    }
}

void DataApi::setStrategy(Strategy *s)
{
    LOG_INFO << s->name();
}

void DataApi::delStrategy(std::string strategyName)
{
}

const QuoteSet& DataApi::getTargetObjectQuoteSet()
{
    return dataApiTargetObjects_;
}
