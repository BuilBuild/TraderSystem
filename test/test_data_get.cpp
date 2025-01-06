/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 23:34:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-05 15:30:55
 * @Description: 
 */
#include <iostream>
#include "DataCenter.h"
#include "DataApi.h"
#include "Strategy.h"

#include <muduo/base/Logging.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>


DataApi* DATA_API = nullptr;
// Logger::LogLevel g_logLevel
// 启动一个线程向DataApi实例里推送数据
void putDataToAdataApi(DataApi *dataApi)
{
    OrderBook orderbook{};
    orderbook.AskPrice1 = 0.1;
    sprintf(orderbook.TargeName, "target_7");
    while(true)
    {
        for(int i=0;i<50; ++i)
        {
            dataApi->PutOrderBook(orderbook);
            orderbook.AskPrice1 += 0.5;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main()
{
#ifdef LOG_DEBUG
    muduo::Logger::Logger::setLogLevel(muduo::Logger::LogLevel::DEBUG);
#endif

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
    std::thread th(putDataToAdataApi, DATA_API);

    th.join();

    getchar();
    return 0; 
}