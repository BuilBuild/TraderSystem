/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 18:14:05
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 18:29:08
 * @Description: 
 */
#pragma once

#include "ExecutionBase.h"

class ExecutionCtpTrader : public ExecutionBase
{
public:
    ExecutionCtpTrader();
    ~ExecutionCtpTrader();
    void onOrderInsert() override;
    void onOrderExecute() override;
    void init() override;

};
