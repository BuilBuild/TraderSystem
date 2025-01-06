/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:46:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 22:29:46
 * @Description: 
 */
#include "CtpApi.h"
#include <iostream>

CtpApi::CtpApi()
    : APIBase()
{
    init();
}

CtpApi::~CtpApi()
{
}

void CtpApi::onOrderBookReceive()
{
}

void CtpApi::init()
{
    using string  = std::string;
    auto t = context_->getJson().at("CTP_API");
    sprintf(loginReq.BrokerID, string(t.at("BrokerID")).c_str());
    sprintf(loginReq.UserID, string(t.at("UserID")).c_str());
    sprintf(loginReq.Password, string(t.at("PassWord")).c_str());
    
    gTradeFrontAddr_ = t.at("gTradeFrontAddr");
    std::cout << loginReq.BrokerID << std::endl;;
    
    auto ic = t.at("InstrumentID");
    for(auto t: ic)
    {
        instrumentId_.emplace_back(t);
    }
    // 开始登陆
    logIn();
}

void CtpApi::logIn()
{
     pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();

}