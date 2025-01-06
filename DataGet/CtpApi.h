/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:45:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 22:20:02
 * @Description: 
 */
#pragma once


#include "APIBase.h"

#include "CTP/ThostFtdcMdApi.h"
#include "CTP/ThostFtdcTraderApi.h"
#include "CTP/ThostFtdcUserApiStruct.h"

#include <string>
#include <vector>

class CtpApi : public APIBase
{
public:
    explicit CtpApi();
    ~CtpApi();

    void onOrderBookReceive() override;
    void init() override;

private:
    void logIn();

private:
    std::string gTradeFrontAddr_;
    // std::string brokerID_;
    // std::string userId_;
    // std::string passWord_;
    std::vector<std::string> instrumentId_;

    CThostFtdcMdApi *pUserApi = nullptr;
    CThostFtdcReqUserLoginField loginReq{};

    
};