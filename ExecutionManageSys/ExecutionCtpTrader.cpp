/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 18:28:23
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-15 00:00:49
 * @Description: 
 */
#include "ExecutionCtpTrader.h"
#include <muduo/base/Logging.h>
#include <string>
#include <iostream>

ExecutionCtpTrader::ExecutionCtpTrader()
    : ExecutionBase(),pUserApi_(CThostFtdcTraderApi::CreateFtdcTraderApi())
{
    traderSpi_ = std::make_shared<TraderSpi>(pUserApi_);
    traderSpi_->setCtpExecuteBase(this);
    
}

ExecutionCtpTrader::~ExecutionCtpTrader()
{
    LOG_INFO << "CTPTrader destroy";
    // pUserApi_->ReqUserLogout()
    // traderSpi_->reqUserLogout();
    pUserApi_->Join();
}

void ExecutionCtpTrader::onOrderInsert()
{
}

void ExecutionCtpTrader::onOrderExecute()
{
}

void ExecutionCtpTrader::init()
{
    using string = std::string;
    auto t = context_->getJson()["ExecutionManage"]["CTPTrader"];
    sprintf(loginReq_.BrokerID, "%s",string(t["BrokerID"]).c_str());
    sprintf(loginReq_.UserID, "%s", string(t["UserID"]).c_str());
    sprintf(loginReq_.Password, "%s", string(t["PassWord"]).c_str());
    sprintf(gTradeFrontAddr, "%s", string(t["gTradeFrontAddr"]).c_str());

    pUserApi_->RegisterSpi(traderSpi_.get());
    pUserApi_->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
	pUserApi_->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
    pUserApi_->RegisterFront(gTradeFrontAddr);

    pUserApi_->Init();
    
    
}

void ExecutionCtpTrader::getPositionInfo()
{
    
}

void ExecutionCtpTrader::reqQueryTradingAccount()
{
    traderSpi_->reqQueryTradingAccount();
}

void ExecutionCtpTrader::executeOrder(Order &order)
{
    // 这里需要进行包装 插入柜台
    std::cout << "get order " << order.TargetName << "  price: " << order.Price << " Direction: "
        << order.Direction << std::endl;
    // traderSpi_->reqOrderInsert(orderInsertReq);
}
