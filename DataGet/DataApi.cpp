/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:41:44
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 22:41:12
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
    for(auto ele : quoterSet_)
    {
        ele->pushDate(orderBook);
    }
}

void QuoteElement::subscribe(Strategy *s)
{
    quoterSet_.insert(s);
}   

std::string QuoteElement::name() const
{
    return name_;
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
    // 初始化订单簿
    for(const auto &t: dataApiTargetObjects_)
    {
        quoteElementMap_.insert(std::pair<std::string, QuoteElement>(t.name, t.name));
    }

}

void DataApi::setStrategy(Strategy *s)
{
    LOG_INFO << s->name();
}

void DataApi::subscribeTarget(Strategy *s, const TargetOBJ &targetOBJ)
{
   auto t =  quoteElementMap_.find(targetOBJ.name);
   
   if(t != quoteElementMap_.end())
   {
        LOG_INFO<< t->second.name() <<  "##### is regist! the strategy name is " << s->name()
            << " TargetOBJ name is " << targetOBJ.name;
        // 向定单簿里注册策略
        t->second.subscribe(s);

   }
   else
   {
        LOG_WARN << t->second.name()  << " regist failed. the strategy name is " << s->name()
            << " TargetOBJ name is " << targetOBJ.name;
   }
}

void DataApi::delStrategy(std::string strategyName)
{
}

const QuoteSet& DataApi::getTargetObjectQuoteSet()
{
    return dataApiTargetObjects_;
}
