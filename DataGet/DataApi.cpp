/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:41:44
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-05 14:43:11
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
    // 利用自旋锁保证拷贝一致
    // orderBookSpinLock_.unlock();
    // memcpy(&orderBook_, &orderBook, sizeof(OrderBook));
    // orderBookSpinLock_.unlock();
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
        // quoteElementMap_.insert(std::pair<std::string, QuoteElement>(t.name, t.name));
        quoteElementMap_.emplace(t.name, t.name);
    }

    // 启动数据分发线程
    threadDistribute_ = std::thread([this]{
        while(true)
        {
            this->OrderDistribute();
        }
    });

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

void DataApi::PutOrderBook(const OrderBook &orderBook)
{
    orderQueue_.emplace(orderBook);
}

void DataApi::OrderDistribute()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto t = orderQueue_.unsafe_size();
    LOG_INFO << "OrderDistribute Func, OrderQueue is empty? " << (orderQueue_.empty()? "true": "false") 
        << " queue size: " << t;
    // 如果队列不为空取出数据更新到订单簿列表
    if(!orderQueue_.empty())
    {   
        OrderBook orderBook{};
        // 如果队列元素获取成功，数据则会写入到orderBook中
        if(orderQueue_.try_pop(orderBook))
        {
            LOG_INFO <<"order name is "<< orderBook.TargeName <<"| get price " << orderBook.AskPrice1;
            // 更新订单簿
            auto c = quoteElementMap_.find(orderBook.TargeName);
            if(c != quoteElementMap_.end())
            {
                LOG_INFO <<"quoteElementMap_ find element success :" << c->second.name();
                c->second.update(orderBook);
            }
            
        }
    
    }
}
