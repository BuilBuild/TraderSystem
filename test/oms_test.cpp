/*
 * @Author: LeiJiulong
 * @Date: 2025-01-10 19:58:44
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-13 21:14:25
 * @Description: 
 */
#include "OrderManager.h"
#include "ExecutionSystem.h"
#include "ExecutionCtpTrader.h"

#include <iostream>

char CONFIG_PATH[] = "/home/leijiulong/temp/TraderSystem-main/ConfigFileDir/config.json";

int main()
{
    ExecutionCtpTrader ctpTrader;
    ExecutionSystem t(&ctpTrader);
    OMS ms(&t);
    getchar();
    t.getTradingInfo();
    getchar();
    return 0;
}
