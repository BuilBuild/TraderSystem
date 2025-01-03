/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:34:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 23:45:12
 * @Description: 
 */
#include <iostream>
#include "DataCenter.h"
#include "DataApi.h"


DataApi* DATA_API = nullptr;

int main()
{
    DATA_API = new DataApi();
    auto t = DataCenter::getInstance();
    std::cout << "hello test_test_get" << std::endl;
    return 0; 
}