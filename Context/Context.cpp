/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 16:13:24
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 21:48:38
 * @Description: 
 */
#include "Context.hpp"


Context* Context::instance_ = nullptr;

std::once_flag Context::flag_;

Context *Context::getInstance()
{
    std::call_once(flag_,Context::construct);
    return instance_;
}

const json& Context::getJson()
{
    return configJson_;
}

Context::Context()
{
    loadConfigFile();
}

Context::~Context()
{
}

void Context::construct()
{
    instance_ = new Context();
}

void Context::loadConfigFile()
{
    std::ifstream f(CONFIG_PATH);
    if(f.is_open())
    {
        std::string json_s((std::istreambuf_iterator<char>(f)),
                std::istreambuf_iterator<char>());
        configJson_ = json::parse(json_s);
        messageHubBindPort_ = configJson_["messageHubBindPort"];
    }
    else
    { 
        LOG_FATAL<< "The config file is exist? please confirm it";
    }
}