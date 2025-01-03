/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:02:22
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 23:57:01
 * @Description: 
 */
#include "Strategy.h"

Strategy::Strategy(std::string nameArg)
    :name_(nameArg)
{
}

void Strategy::pushDate(const OrderBook &)
{
}

std::string Strategy::name() const
{
    return name_;
}
