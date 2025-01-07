/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 18:28:23
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 19:22:22
 * @Description: 
 */
#include "ExecutionCtpTrader.h"
#include <muduo/base/Logging.h>

ExecutionCtpTrader::ExecutionCtpTrader()
    : ExecutionBase()
{
}

ExecutionCtpTrader::~ExecutionCtpTrader()
{
    LOG_INFO << "CTPTrader destroy";
}

void ExecutionCtpTrader::onOrderInsert()
{
}

void ExecutionCtpTrader::onOrderExecute()
{
}

void ExecutionCtpTrader::init()
{
    LOG_INFO << "CTPTrader init";
}
