/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 19:35:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 21:12:30
 * @Description: 
 */

#include "CTPTraderApi.h"
#include <iostream>
#include <string.h>
#include <thread>

void TraderSpi::OnFrontConnected()
{
    std::cout << "=====建立网络连接成功=====" << std::endl;
	// 开始登录
	// reqUserLogin();
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
	{
		std::cout << "=====账户登录成功=====" << std::endl;
		loginFlag = true;
		std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "登录时间： " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "经纪商： " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;
		// 保存会话参数
		trade_front_id = pRspUserLogin->FrontID;
		session_id = pRspUserLogin->SessionID;
		strcpy(order_ref, pRspUserLogin->MaxOrderRef);

		// 投资者结算结果确认
		reqSettlementInfoConfirm();

    }

}

void TraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    isErrorRspInfo(pRspInfo);
}

void TraderSpi::OnFrontDisconnected(int nReason)
{
    std::cerr << "=====网络连接断开=====" << std::endl;
	std::cerr << "错误码： " << nReason << std::endl;
}

void TraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
    std::cerr << "=====网络心跳超时=====" << std::endl;
	std::cerr << "距上次连接时间： " << nTimeLapse << std::endl;
}

void TraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
	{
		loginFlag = false; // 登出就不能再交易了 
		std::cout << "=====账户登出成功=====" << std::endl;
		std::cout << "经纪商： " << pUserLogout->BrokerID << std::endl;
		std::cout << "帐户名： " << pUserLogout->UserID << std::endl;
	}
}

void TraderSpi::reqUserLogin()
{
    std::cout << "开始登录" << std::endl;
    CThostFtdcReqUserLoginField loginReq{};
	strcpy(loginReq.BrokerID, "9999");
	strcpy(loginReq.UserID, "***");
	strcpy(loginReq.Password, "***");
	static int requestID = 0; // 请求编号
	int rt = m_pUserApi->ReqUserLogin(&loginReq, requestID);
	if (!rt)
		std::cout << ">>>>>>发送登录请求成功" << std::endl;
	else
		std::cerr << "--->>>发送登录请求失败" << std::endl;
}

void TraderSpi::reqUserLogout()
{
    CThostFtdcUserLogoutField logoutReq{};
	strcpy(logoutReq.BrokerID, "9999");
	strcpy(logoutReq.UserID, "***");
	static int requestID = 0; // 请求编号
	int rt = m_pUserApi->ReqUserLogout(&logoutReq, requestID);
	if (!rt)
		std::cout << ">>>>>>发送登出请求成功" << std::endl;
	else
		std::cerr << "--->>>发送登出请求失败" << std::endl;
}

void TraderSpi::reqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField settlementConfirmReq{};
    strcpy(settlementConfirmReq.BrokerID, "9999");
	strcpy(settlementConfirmReq.InvestorID, "***");
    static int requestID = 0; // 请求编号
	int rt = m_pUserApi->ReqSettlementInfoConfirm(&settlementConfirmReq, requestID);
    if (!rt)
		std::cout << ">>>>>>发送投资者结算结果确认请求成功" << std::endl;
	else
		std::cerr << "--->>>发送投资者结算结果确认请求失败" << std::endl;

}

void TraderSpi::reqQueryInstrument()
{
	/*
	///查询合约
	struct CThostFtdcQryInstrumentField
	{
		///合约代码
		TThostFtdcInstrumentIDType	InstrumentID;
		///交易所代码
		TThostFtdcExchangeIDType	ExchangeID;
		///合约在交易所的代码
		TThostFtdcExchangeInstIDType	ExchangeInstID;
		///产品代码
		TThostFtdcInstrumentIDType	ProductID;
	};
	*/
    CThostFtdcQryInstrumentField instrumentReq;
	memset(&instrumentReq, 0, sizeof(instrumentReq));
	strcpy(instrumentReq.InstrumentID, "au2410");
	strcpy(instrumentReq.ExchangeInstID, "au2410");//au2410C568
	strcpy(instrumentReq.ExchangeID, "SHFE");
	
	
	static int requestID = 0; // 请求编号
	/////合约在交易所的代码 不确定的时候会发送所有的查询
	int rt = m_pUserApi->ReqQryInstrument(&instrumentReq, requestID);
	if (!rt)
		std::cout << ">>>>>>发送合约查询请求成功" << std::endl;
	else
		std::cerr << "--->>>发送合约查询请求失败" << std::endl;

}

void TraderSpi::reqQueryTradingAccount()
{
    CThostFtdcQryTradingAccountField tradingAccountReq{};
	strcpy(tradingAccountReq.BrokerID, "9999");
	strcpy(tradingAccountReq.InvestorID, "***");
	static int requestID = 0; // 请求编号
	std::this_thread::sleep_for(std::chrono::milliseconds(700)); // 有时候需要停顿一会才能查询成功
	int rt = m_pUserApi->ReqQryTradingAccount(&tradingAccountReq, requestID);
	if (!rt)
		std::cout << ">>>>>>发送投资者资金账户查询请求成功" << std::endl;
	else
		std::cerr << "--->>>发送投资者资金账户查询请求失败" << std::endl;
}

void TraderSpi::reqQueryInvestorPosition()
{
    CThostFtdcQryInvestorPositionField postionReq;
	memset(&postionReq, 0, sizeof(postionReq));
	strcpy(postionReq.BrokerID, "9999");
	strcpy(postionReq.InvestorID, "****");
	strcpy(postionReq.InstrumentID, "au2410");
	static int requestID = 0; // 请求编号
	std::this_thread::sleep_for(std::chrono::milliseconds(700)); // 有时候需要停顿一会才能查询成功
	int rt = m_pUserApi->ReqQryInvestorPosition(&postionReq, requestID);
	if (!rt)
		std::cout << ">>>>>>发送投资者持仓查询请求成功" << std::endl;
	else
		std::cerr << "--->>>发送投资者持仓查询请求失败" << std::endl;

}

void TraderSpi::reqOrderInsert()
{
    CThostFtdcInputOrderField orderInsertReq{};
	memset(&orderInsertReq, 0, sizeof(orderInsertReq));
	///经纪公司代码
	strcpy(orderInsertReq.BrokerID, "9999");
	///投资者代码
	strcpy(orderInsertReq.InvestorID, "***");
	///合约代码
	strcpy(orderInsertReq.InstrumentID, "au2410");
	///报单引用
	strcpy(orderInsertReq.OrderRef, order_ref);
	///报单价格条件: 限价
	orderInsertReq.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///买卖方向: 
    TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
	orderInsertReq.Direction = gTradeDirection;
	///组合开平标志: 开仓
	orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	///组合投机套保标志
	orderInsertReq.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	///价格
    TThostFtdcPriceType gLimitPrice = 22735;  
	orderInsertReq.LimitPrice = gLimitPrice;
	///数量：1
	orderInsertReq.VolumeTotalOriginal = 1;
	///有效期类型: 当日有效
	orderInsertReq.TimeCondition = THOST_FTDC_TC_GFD;
	///成交量类型: 任何数量
	orderInsertReq.VolumeCondition = THOST_FTDC_VC_AV;
	///最小成交量: 1
	orderInsertReq.MinVolume = 1;
	///触发条件: 立即
	orderInsertReq.ContingentCondition = THOST_FTDC_CC_Immediately;
	///强平原因: 非强平
	orderInsertReq.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///自动挂起标志: 否
	orderInsertReq.IsAutoSuspend = 0;
	///用户强评标志: 否
	orderInsertReq.UserForceClose = 0;

	static int requestID = 0; // 请求编号
	int rt = m_pUserApi->ReqOrderInsert(&orderInsertReq, ++requestID);
	if (!rt)
		std::cout << ">>>>>>发送报单录入请求成功" << std::endl;
	else
		std::cerr << "--->>>发送报单录入请求失败" << std::endl;
}

void TraderSpi::reqOrderAction(CThostFtdcOrderField *pOrder)
{
    static bool orderActionSentFlag = false; // 是否发送了报单
	if (orderActionSentFlag)
		return;

	CThostFtdcInputOrderActionField orderActionReq;
	memset(&orderActionReq, 0, sizeof(orderActionReq));
	///经纪公司代码
	strcpy(orderActionReq.BrokerID, pOrder->BrokerID);
	///投资者代码
	strcpy(orderActionReq.InvestorID, pOrder->InvestorID);
	///报单操作引用
	//	TThostFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	strcpy(orderActionReq.OrderRef, pOrder->OrderRef);
	///请求编号
	//	TThostFtdcRequestIDType	RequestID;
	///前置编号
	orderActionReq.FrontID = trade_front_id;
	///会话编号
	orderActionReq.SessionID = session_id;
	///交易所代码
	//	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	//	TThostFtdcOrderSysIDType	OrderSysID;
	///操作标志
	orderActionReq.ActionFlag = THOST_FTDC_AF_Delete;
	///价格
	//	TThostFtdcPriceType	LimitPrice;
	///数量变化
	//	TThostFtdcVolumeType	VolumeChange;
	///用户代码
	//	TThostFtdcUserIDType	UserID;
	///合约代码
	strcpy(orderActionReq.InstrumentID, pOrder->InstrumentID);
	static int requestID = 0; // 请求编号
	int rt = m_pUserApi->ReqOrderAction(&orderActionReq, ++requestID);
	if (!rt)
		std::cout << ">>>>>>发送报单操作请求成功" << std::endl;
	else
		std::cerr << "--->>>发送报单操作请求失败" << std::endl;
	orderActionSentFlag = true;

}

bool TraderSpi::isErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
	return bResult;
}

bool TraderSpi::isMyOrder(CThostFtdcOrderField *pOrder)
{
    return ((pOrder->FrontID == trade_front_id) &&
		(pOrder->SessionID == session_id) &&
		(strcmp(pOrder->OrderRef, order_ref) == 0));
}

bool TraderSpi::isTradingOrder(CThostFtdcOrderField *pOrder)
{
    return ((pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_AllTraded));
}

void TraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
	{
		std::cout << "=====投资者结算结果确认成功=====" << std::endl;
		std::cout << "确认日期： " << pSettlementInfoConfirm->ConfirmDate << std::endl;
		std::cout << "确认时间： " << pSettlementInfoConfirm->ConfirmTime << std::endl;
		// 请求查询合约
		reqQueryInstrument();
	}
}

void TraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
	{
		std::cout << "=====查询合约结果成功=====" << std::endl;
		std::cout << "交易所代码： " << pInstrument->ExchangeID << std::endl;
		std::cout << "合约代码： " << pInstrument->InstrumentID << std::endl;
		std::cout << "合约在交易所的代码： " << pInstrument->ExchangeInstID << std::endl;
		std::cout << "执行价： " << pInstrument->StrikePrice << std::endl;
		std::cout << "到期日： " << pInstrument->EndDelivDate << std::endl;
		std::cout << "当前交易状态： " << pInstrument->IsTrading << std::endl;
		// 请求查询投资者资金账户
		reqQueryTradingAccount();
	}
}

void TraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
	{
		std::cout << "=====查询投资者资金账户成功=====" << std::endl;
		std::cout << "投资者账号： " << pTradingAccount->AccountID << std::endl;
		std::cout << "可用资金： " << pTradingAccount->Available << std::endl;
		std::cout << "可取资金： " << pTradingAccount->WithdrawQuota << std::endl;
		std::cout << "当前保证金: " << pTradingAccount->CurrMargin << std::endl;
		std::cout << "平仓盈亏： " << pTradingAccount->CloseProfit << std::endl;
		// 请求查询投资者持仓
		reqQueryInvestorPosition();
	}
}

void TraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
	{
		std::cout << "=====查询投资者持仓成功=====" << std::endl;
		if (pInvestorPosition)
		{
			std::cout << "合约代码： " << pInvestorPosition->InstrumentID << std::endl;
			std::cout << "开仓价格： " << pInvestorPosition->OpenAmount << std::endl;
			std::cout << "开仓量： " << pInvestorPosition->OpenVolume << std::endl;
			std::cout << "开仓方向： " << pInvestorPosition->PosiDirection << std::endl;
			std::cout << "占用保证金：" << pInvestorPosition->UseMargin << std::endl;
		}
		else
			std::cout << "----->该合约未持仓" << std::endl;
		
		// 报单录入请求（这里是一部接口，此处是按顺序执行）
		/*if (loginFlag)
			reqOrderInsert();*/
		//if (loginFlag)
		//	reqOrderInsertWithParams(g_pTradeInstrumentID, gLimitPrice, 1, gTradeDirection); // 自定义一笔交易

		// 策略交易
		std::cout << "=====开始进入策略交易=====" << std::endl;

		// while (loginFlag)
		// 	StrategyCheckAndTrade(g_pTradeInstrumentID, this);
	}
}

void TraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
	{
		std::cout << "=====报单录入成功=====" << std::endl;
		std::cout << "合约代码： " << pInputOrder->InstrumentID << std::endl;
		std::cout << "价格： " << pInputOrder->LimitPrice << std::endl;
		std::cout << "数量： " << pInputOrder->VolumeTotalOriginal << std::endl;
		std::cout << "开仓方向： " << pInputOrder->Direction << std::endl;
	}
}

void TraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
	{
		std::cout << "=====报单操作成功=====" << std::endl;
		std::cout << "合约代码： " << pInputOrderAction->InstrumentID << std::endl;
		std::cout << "操作标志： " << pInputOrderAction->ActionFlag;
	}
}

void TraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    char str[10];
	sprintf(str, "%d", pOrder->OrderSubmitStatus);
	int orderState = atoi(str) - 48;	//报单状态0=已经提交，3=已经接受

	std::cout << "=====收到报单应答=====" << std::endl;

	if (isMyOrder(pOrder))
	{
		if (isTradingOrder(pOrder))
		{
			std::cout << "--->>> 等待成交中！" << std::endl;
			//reqOrderAction(pOrder); // 这里可以撤单
			//reqUserLogout(); // 登出测试
		}
		else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
			std::cout << "--->>> 撤单成功！" << std::endl;
	}
}

void TraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    std::cout << "=====报单成功成交=====" << std::endl;
	std::cout << "成交时间： " << pTrade->TradeTime << std::endl;
	std::cout << "合约代码： " << pTrade->InstrumentID << std::endl;
	std::cout << "成交价格： " << pTrade->Price << std::endl;
	std::cout << "成交量： " << pTrade->Volume << std::endl;
	std::cout << "开平仓方向： " << pTrade->Direction << std::endl;

}

void TraderSpi::reqOrderInsert(TThostFtdcInstrumentIDType instrumentID, TThostFtdcPriceType price, TThostFtdcVolumeType volume, TThostFtdcDirectionType direction)
{
    CThostFtdcInputOrderField orderInsertReq;
	memset(&orderInsertReq, 0, sizeof(orderInsertReq));
	///经纪公司代码
	strcpy(orderInsertReq.BrokerID, "9999");
	///投资者代码
	strcpy(orderInsertReq.InvestorID, "***");
	///合约代码
	strcpy(orderInsertReq.InstrumentID, "au2410");
	///报单引用
	strcpy(orderInsertReq.OrderRef, order_ref);
	///报单价格条件: 限价
	orderInsertReq.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///买卖方向:
    TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;
	orderInsertReq.Direction = gTradeDirection;
	///组合开平标志: 开仓
	orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	///组合投机套保标志
	orderInsertReq.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	///价格
	orderInsertReq.LimitPrice = 570;
	///数量：1
	orderInsertReq.VolumeTotalOriginal = 1;
	///有效期类型: 当日有效
	orderInsertReq.TimeCondition = THOST_FTDC_TC_GFD;
	///成交量类型: 任何数量
	orderInsertReq.VolumeCondition = THOST_FTDC_VC_AV;
	///最小成交量: 1
	orderInsertReq.MinVolume = 1;
	///触发条件: 立即
	orderInsertReq.ContingentCondition = THOST_FTDC_CC_Immediately;
	///强平原因: 非强平
	orderInsertReq.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///自动挂起标志: 否
	orderInsertReq.IsAutoSuspend = 0;
	///用户强评标志: 否
	orderInsertReq.UserForceClose = 0;

	static int requestID = 0; // 请求编号
	int rt = m_pUserApi->ReqOrderInsert(&orderInsertReq, ++requestID);
	if (!rt)
		std::cout << ">>>>>>发送报单录入请求成功" << std::endl;
	else
		std::cerr << "--->>>发送报单录入请求失败" << std::endl;

}