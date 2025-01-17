/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:46:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 02:19:10
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

void CtpApi::onOrderBookReceive(OrderBook &orderBook)
{
    orderBookQueue_.emplace(orderBook);
    // std::cout << orderBookQueue_.size() << "  "<< orderBook.TargeName << "  " << orderBook.LastPrice << std::endl;

}

void CtpApi::init()
{
    using string  = std::string;
    auto t = context_->getJson().at("CTP_API");
    sprintf(loginReq.BrokerID,"%s",string(t.at("BrokerID")).c_str());
    sprintf(loginReq.UserID,"%s", string(t.at("UserID")).c_str());
    sprintf(loginReq.Password,"%s", string(t.at("PassWord")).c_str());
    gTradeFrontAddr_ = t.at("gTradeFrontAddr");
    sprintf(FrontAddr, "%s", gTradeFrontAddr_.c_str());
    
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
    pUserApi->Init();

}




int CTPMdSpi::requestID_ = 0;

CTPMdSpi::CTPMdSpi(CtpApi *ctpApi)
    :ctpApi_(ctpApi),pUserApi_(ctpApi->pUserApi),instrumentId_(new const char*[ctpApi->instrumentId_.size()]),
    instrumentSize_(ctpApi->instrumentId_.size())
{
    std::cout << "CTPMdSpi create" << std::endl;
    for(int i = 0; i <instrumentSize_; ++i)
    {
        instrumentId_[i] = ctpApi_->instrumentId_[i].c_str();
    }
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
        LOG_INFO << ctpApi_->instrumentId_.data();
        int iResult = pUserApi_->SubscribeMarketData(const_cast<char**> (instrumentId_),instrumentSize_);
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
    std::cout << "=====订阅行情成功=====" << std::endl;
	std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
}

void CTPMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTPMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    // 这里可以将数据写入第三方
    OrderBook orderBook{};
    memcpy(orderBook.TargeName, pDepthMarketData->InstrumentID, sizeof(pDepthMarketData->InstrumentID));
    memcpy(orderBook.InstrumentID, pDepthMarketData->InstrumentID,sizeof(pDepthMarketData->InstrumentID));
    
    memcpy(orderBook.TradingDay, pDepthMarketData->TradingDay,sizeof(pDepthMarketData->TradingDay));
    orderBook.LastPrice = pDepthMarketData->LastPrice;
    orderBook.Volume = pDepthMarketData->Volume;
    
    ctpApi_->onOrderBookReceive(orderBook);
}

void CTPMdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTPMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
