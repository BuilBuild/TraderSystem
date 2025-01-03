/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:20:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 23:09:34
 * @Description: 
 */
#pragma once
#include "BaseType.hpp"

#include <tbb/concurrent_unordered_map.h>

class Strategy
{
public:
    void pushDate(const OrderBook&);

};