/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 12:49:06
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 18:04:21
 * @Description: 基础数据类型描述
 */
#pragma once

#include <sys/types.h>
#include <string>


enum TargetType
{
    futures=0,
    stock
};

/**
 * @brief 每次更新的数据基础元素
 */
typedef struct OrderBookElement
{
    char TargeName[128];
    int64_t UpdateTime;
    TargetType OType;
	/// 交易日
	char TradingDay[9];
	/// 合约代码
	char InstrumentID[31];
	/// 交易所代码
	char ExchangeID[9];
	/// 最新价格
	double LastPrice;
	/// 上次结算价
	double PreSettlementPrice;
	/// 数量
	int Volume;
	// 持仓量
	double OpenInterest;
    ///申买价一
    double	BidPrice1;
	///申买量一
	int	BidVolume1;
	///申卖价一
	double	AskPrice1;
	///申卖量一
	int	AskVolume1;
	///申买价二
	double	BidPrice2;
	///申买量二
	int	BidVolume2;
	///申卖价二
	double	AskPrice2;
	///申卖量二
	int	AskVolume2;
	///申买价三
	double	BidPrice3;
	///申买量三
	int	BidVolume3;
	///申卖价三
	double AskPrice3;
	///申卖量三
	int	AskVolume3;
	///申买价四
	double	BidPrice4;
	///申买量四
	int	BidVolume4;
	///申卖价四
	double	AskPrice4;
	///申卖量四
	int	AskVolume4;
	///申买价五
	double	BidPrice5;
	///申买量五
	int	BidVolume5;
	///申卖价五
	double	AskPrice5;
	///申卖量五
	int	AskVolume5;
    // 外部回调指针
    // void* MsgHandle;
} OrderBook;

typedef struct InputOrderField
{
	/// 经济公司代码
	char BrokerId[11];
	/// 投资者代码
	char InvestorId[13];
	/// 合约代码
	char InstrumentID[31];
	/// 报单引用
	char OrderRef[13];
	/// 用户代码
	char UserID[16];
	/// 报价价格条件
	char OrderPriceType;
	/// 买卖方向
	char Direction;
	/// 组合开平标志
	char CombOffsetFlag[5];
	/// 价格
	double LimitPrice;
	/// 数量
	int VolumeTotalOriginal;

} InputOrderField;

typedef struct Order
{
	/// 归属策略
	char StrategyName[31];
	/// 归属用户
	char UserName[31];
	/// 标的名称
	char TargetName[11];
	/// 价格
	double Price;
	/// 数量
	double Volume;
	/// 买卖方向
	char Direction;

} Order;

/**
 * @brief 标的信息
 */
typedef struct TargetOBJ
{
	std::string name;
	//比较运算符重载,按位置排序
	bool operator <(const TargetOBJ & a) const
	{
		return this->name < a.name;
	}
} TargetOBJ;



/**
 * @brief 用于类不可复制继承
 */
class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator = (const noncopyable&) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};