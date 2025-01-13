/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 14:08:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-11 19:44:07
 * @Description: 
 */
#pragma once

#include "zhelpers.h"
#include "Context.hpp"

#include <muduo/base/Logging.h>
#include <zmq.hpp>
#include <mutex>
#include <thread>
#include <functional>
#include <chrono>

#include <iostream>


class MessagingHub
{
public:
    MessagingHub();
    ~MessagingHub()
    {
        runThread_.join();
    }

    void start();

public:
    void run();
private:
    
    zmq::context_t context_;
    zmq::socket_t publisher_;
    
    std::thread runThread_; 

};



