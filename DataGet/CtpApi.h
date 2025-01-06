/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 19:45:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 23:59:09
 * @Description: 
 */
#pragma once


#include "APIBase.h"
#include "BaseType.hpp"

#include "CTP/ThostFtdcMdApi.h"
#include "CTP/ThostFtdcTraderApi.h"
#include "CTP/ThostFtdcUserApiStruct.h"

#include <string>
#include <vector>
#include <memory>


class CTPMdSpi;


static char FrontAddr[128];

class CtpApi : public APIBase
{
    friend class CTPMdSpi;
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
    std::shared_ptr<CTPMdSpi> ctpMdSpi_;
    
};

class CTPMdSpi : public CThostFtdcMdSpi, public noncopyable
{
public:
    static int requestID_;
public:
    CTPMdSpi(CtpApi* ctpApi);
    ~CTPMdSpi();
    CtpApi *ctpApi_;
    CThostFtdcMdApi *pUserApi_;
// 用于回调
public:
    bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
    // 当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。 1
    void OnFrontConnected();
    /// 当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。2
    ///@param nReason 错误原因
    ///         0x1001 网络读失败
    ///         0x1002 网络写失败
    ///         0x2001 接收心跳超时
    ///         0x2002 发送心跳失败
    ///         0x2003 收到错误报文
    void OnFrontDisconnected(int nReason);

    /// 心跳超时警告。当长时间未收到报文时，该方法被调用。
    ///@param nTimeLapse 距离上次接收报文的时间
    void OnHeartBeatWarning(int nTimeLapse);

    /// 登录请求响应 3
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /// 登出请求响应 4
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /// 错误应答
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /// 订阅行情应答
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /// 取消订阅行情应答
    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /// 深度行情通知
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

    // 订阅询价应答
    void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    // 取消订阅询价应答
    void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

};