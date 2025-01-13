/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 17:22:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-13 22:38:06
 * @Description: 
 */

#include "ExecutionSystem.h"
#include <muduo/base/Logging.h>
#include <iostream>



ExecutionSystem::ExecutionSystem(ExecutionBase *execution)
    : executionBase_(execution)
{
    executionBase_->init();
    executeThread_ = std::thread([this]{
        while(true)
        {
            Order order;
            // 当订单队列为空时，队列会堵塞在这里

            orderQueue_.pop(order);
            this->executeOrder(order);
            std::cout << "执行器具执行了订单 " << __LINE__ << std::endl;

        }
    });
}

ExecutionSystem::~ExecutionSystem()
{
    LOG_INFO << "ExecutionSystem destroy";
}

void ExecutionSystem::orderPut(const Order &order)
{
    // std::cout << "执行器收到订单" << std::endl;
    orderQueue_.emplace(order);
}

void ExecutionSystem::orderGet()
{
}

void ExecutionSystem::getPositionInfo()
{
    // executionBase_
}

void ExecutionSystem::getTradingInfo()
{
    executionBase_->reqQueryTradingAccount();
}

void ExecutionSystem::executeOrder(Order &order)
{
    executionBase_->executeOrder(order);
    std::cout << "Execution Order: prise is  "  << order.Price << std::endl;
}
