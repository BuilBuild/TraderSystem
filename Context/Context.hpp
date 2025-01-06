/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 14:28:20
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 15:04:53
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

Context* Context::instance_ = nullptr;

std::once_flag Context::flag_;

inline Context *Context::getInstance()
{
    std::call_once(flag_,Context::construct);
    return instance_;
}

inline Context::Context()
{
    loadConfigFile();
}

inline Context::~Context()
{
}

void Context::construct()
{
    instance_ = new Context();
}

inline void Context::loadConfigFile()
{
    std::ifstream f(CONFIG_PATH);
    if(f.is_open())
    {
        std::string json_s((std::istreambuf_iterator<char>(f)),
                std::istreambuf_iterator<char>());
        configJson_ = json::parse(json_s);
    }
    else
    { 
        LOG_FATAL<< "The config file is exist? please confirm it";
    }
}
