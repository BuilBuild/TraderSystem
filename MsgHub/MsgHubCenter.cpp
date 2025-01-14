/*
 * @Author: LeiJiulong
 * @Date: 2025-01-14 22:36:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-14 23:59:20
 * @Description: 
 */

#include "MsgHubCenter.h"
#include "json.hpp"

#include <muduo/base/Logging.h>


MsgHubCenter::MsgHubCenter(Context *configCtx)
    :ctx_(1),configContext_(configCtx),XSUP_(ctx_, zmq::socket_type::xsub),
    XPUB_(ctx_, zmq::socket_type::xpub)
{
    // 绑定地址
    auto t = configContext_->getJson()["MsgHubCenter"];
    XSUP_.bind(t["XSUBBindAddr"]);
    XPUB_.bind(t["XPUBBindAddr"]);
    LOG_INFO << "MsgHubCenter XSUB Bind: " << std::string(t["XSUBBindAddr"]);
    LOG_INFO << "MsgHubCenter XPUB Bind: " << std::string(t["XPUBBindAddr"]);
    run();
}

MsgHubCenter::~MsgHubCenter()
{
    stop();
}

void MsgHubCenter::stop()
{
    XPUB_.close();
    XSUP_.close();
    ctx_.close();
}

void MsgHubCenter::run()
{
    LOG_INFO << "Message Center start " << __func__;
    zmq::proxy_steerable(XPUB_,XSUP_, nullptr, nullptr);
}
