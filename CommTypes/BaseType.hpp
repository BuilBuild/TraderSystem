/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 12:49:06
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-05 15:06:58
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