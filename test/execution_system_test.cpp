/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 19:09:32
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 23:31:16
 * @Description: 
 */
#include "ExecutionSystem.h"
#include "ExecutionCtpTrader.h"

#include <iostream>
#include <thread>

char CONFIG_PATH[] = "/home/leijiulong/temp/TraderSystem-main/ConfigFileDir/config.json";

int main()
{
    
    std::cout << "Execution_system_test" << std::endl;
    ExecutionCtpTrader ctpTrader;
    ExecutionSystem t(&ctpTrader);
    getchar();
    
    t.getTradingInfo();
    getchar();
    return 0;
}
