/*
 * @Author: LeiJiulong
 * @Date: 2025-01-07 17:39:13
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-07 17:39:15
 * @Description: 
 */
#include "ExecutionBase.h"

ExecutionBase::ExecutionBase()
{
    // 获得上下文对象指针
    context_ = Context::getInstance();
}