/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 14:28:20
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 16:13:09
 * @Description: 
 */
#pragma once

#include "json.hpp"

#include <string>
#include <mutex>
#include <fstream>
#include <muduo/base/Logging.h>


using json = nlohmann::json;



extern char CONFIG_PATH[];

class Context
{
public:
    static Context* getInstance();

    std::string messageHubBindPort() const
    {
        return messageHubBindPort_;
    }

private:
    Context();
    ~Context();
    static void construct();
    void loadConfigFile();
private:
    static Context* instance_;
    static std::once_flag flag_;
    json configJson_;
    std::string messageHubBindPort_;
};


