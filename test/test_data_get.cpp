/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:34:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 16:34:00
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
    Strategy s1 = Strategy("s1",t);
    Strategy s2 = Strategy("s1",t);
    std::cout << "hello test_test_get" << std::endl;

    getchar();
    return 0; 
}