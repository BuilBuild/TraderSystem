/*
 * @Author: LeiJiulong
 * @Date: 2025-01-14 22:36:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-14 22:56:54
 * @Description: 用于分发各类消息
 */

#pragma once

#include "Context.hpp"
#include "BaseType.hpp"

#include <zmq.hpp>

class MsgHubCenter : noncopyable
{
public:
    explicit MsgHubCenter(Context *configCtx);
    ~MsgHubCenter();

    /**
     * @brief 停止 后期可用中断信号来配置
     */
    void stop();
    
private:
    /**
     * @brief 启动消息队列分发中心
     */
    void run();
private:
    // 消息队列配置
    zmq::context_t ctx_;    // 上下文
    zmq::socket_t XSUP_;    // XSUB socket
    zmq::socket_t XPUB_;    // XPUB socket

    // 配置文件对象的指针
    Context *configContext_;

};


