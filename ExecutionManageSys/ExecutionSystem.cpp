/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 17:22:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 19:15:59
 * @Description: 
 */

#include "ExecutionSystem.h"
#include <muduo/base/Logging.h>



ExecutionSystem::ExecutionSystem(ExecutionBase *execution)
    : executionBase_(execution)
{
    executionBase_->init();
}

ExecutionSystem::~ExecutionSystem()
{
    LOG_INFO << "ExecutionSystem destroy";
}

void ExecutionSystem::orderPut(const Order &order)
{
    orderQueue_.emplace(order);
}

void ExecutionSystem::orderGet()
{
}
