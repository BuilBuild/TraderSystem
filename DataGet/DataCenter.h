/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 21:51:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 22:59:07
 * @Description: 
 */
#pragma once

#include "BaseType.hpp"
#include "Strategy.h"

#include<string>
#include <spdlog/spdlog.h>
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_vector.h>


class DataApi;

/**
 * @brief 
 */
class DataCenter
{
    using QuoteList = tbb::concurrent_vector<std::string>;
public:

private:

private:
    // 封装号的数据接口
    DataApi* dataApi_;
    // 订阅列表
    QuoteList quoteList_;
    
    
};