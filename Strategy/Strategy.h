/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 22:20:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 23:56:13
 * @Description: 
 */
#pragma once
#include "BaseType.hpp"

#include <tbb/concurrent_unordered_map.h>
#include <string>

class Strategy
{
public:
    explicit Strategy(std::string);
    void pushDate(const OrderBook&);

    std::string name() const ;
private:

private:
    std::string name_;

};