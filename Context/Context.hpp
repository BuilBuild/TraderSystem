/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 14:28:20
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-10 19:56:39
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

/**
 * @brief 上下文对象，存储着json配置文件的配置信息
 */
class Context
{
public:
    static Context* getInstance();

    std::string messageHubBindPort() const
    {
        return messageHubBindPort_;
    }
    
    const json& getJson();
    std::string filePath() const;

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
    std::string filePath_;
};


