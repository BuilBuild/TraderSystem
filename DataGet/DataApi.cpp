/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:41:44
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 23:44:43
 * @Description: 
 */
#include "DataApi.h"

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
}
