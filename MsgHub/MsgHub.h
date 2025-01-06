/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 14:08:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 14:26:37
 * @Description: 
 */
#pragma once

#include "zhelpers.h"

#include <zmq.hpp>
#include <mutex>


class MessagingHub
{
public:


private:
    zmq::context_t context;
    zmq::socket_t publisher;


};



