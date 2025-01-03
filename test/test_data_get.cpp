/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:34:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 23:52:57
 * @Description: 
 */
#include <iostream>
#include "DataCenter.h"
#include "DataApi.h"
#include "Strategy.h"


DataApi* DATA_API = nullptr;

int main()
{
    DATA_API = new DataApi();
    auto t = DataCenter::getInstance();
    Strategy st = Strategy("s1");
    std::cout << "hello test_test_get" << std::endl;
    t->setStrategy(&st);
    getchar();
    return 0; 
}