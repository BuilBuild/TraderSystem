/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:46:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 00:07:30
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
    
    pUserApi->Join();
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
    sprintf(FrontAddr, gTradeFrontAddr_.c_str());

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
    ctpMdSpi_ = std::make_shared<CTPMdSpi>(this);
    pUserApi->RegisterSpi(ctpMdSpi_.get());
    pUserApi->RegisterFront(FrontAddr);
    std::cout << FrontAddr << std::endl;
    pUserApi->Init();

}




int CTPMdSpi::requestID_ = 0;

CTPMdSpi::CTPMdSpi(CtpApi *ctpApi)
    :ctpApi_(ctpApi),pUserApi_(ctpApi->pUserApi)
{
    std::cout << "CTPMdSpi create" << std::endl;
    
}

CTPMdSpi::~CTPMdSpi()
{
    std::cout << "CTPMdSpi destroy" << std::endl;
}

bool CTPMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    return false;
}

void CTPMdSpi::OnFrontConnected()
{
    
    LOG_INFO << "开始连接 并开始登陆....";
    pUserApi_->ReqUserLogin(&ctpApi_->loginReq, ++requestID_);
    
}

void CTPMdSpi::OnFrontDisconnected(int nReason)
{
}

void CTPMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
}

void CTPMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(0 != pRspInfo->ErrorID)
    {
        LOG_INFO << "登陆失败， 响应码： " << pRspInfo ->ErrorID << " 原因：" << pRspInfo->ErrorMsg;
    }
    else
    {
        LOG_INFO << "登陆成功，日期为： " << pUserApi_->GetTradingDay();
    }
}

void CTPMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTPMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTPMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTPMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTPMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
}

void CTPMdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTPMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
