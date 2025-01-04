/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:34:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-04 20:57:01
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
    Strategy s2 = Strategy("s2",t);
    std::cout << "hello test_test_get" << std::endl;
    TargetOBJ a{"hello"};
    TargetOBJ targetList[] = {
        {"t1"}, {"t2"},{"t2"}, {"t3"}, {"target_7"}
    };
    s1.subScribeTargetOne(a);
    s1.subScribeTargets(targetList, 5);

    getchar();
    return 0; 
}