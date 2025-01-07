/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 18:14:05
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 22:00:17
 * @Description: 
 */
#pragma once

#include "ExecutionBase.h"
#include "CTP/ThostFtdcUserApiStruct.h"
#include "CTP/ThostFtdcTraderApi.h"
#include "CTPTraderApi.h"

#include <memory>

class TraderSpi;

class ExecutionCtpTrader : public ExecutionBase
{
    friend class TraderSpi;
public:
    ExecutionCtpTrader();
    ~ExecutionCtpTrader();
    void onOrderInsert() override;
    void onOrderExecute() override;
    /**
     * @brief 读取配置文件并初始化数据源
     */
    void init() override;
    /**
     * @brief  获取持仓信息
     */
    void getPositionInfo() override;
    /**
     * @brief 查询资金信息
     */
    void reqQueryTradingAccount() override;
    
public:
    CThostFtdcTraderApi* pUserApi_;

private:
    ///用户登录请求 存储了用户登陆的信息，在init函数写入用户相关信息
    CThostFtdcReqUserLoginField loginReq_{};
    std::shared_ptr<TraderSpi> traderSpi_;
    // 前置地址端口
    char gTradeFrontAddr[128]{};
};
