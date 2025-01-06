/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:45:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 19:59:08
 * @Description: 
 */
#pragma once


#include "APIBase.h"
#include "CTP/ThostFtdcMdApi.h"
#include "CTP/ThostFtdcTraderApi.h"
#include "CTP/ThostFtdcUserApiStruct.h"

class CtpApi : public APIBase
{
public:
    explicit CtpApi();
    ~CtpApi();

    void onOrderBookReceive() override;
    void init() override;

private:
    
};