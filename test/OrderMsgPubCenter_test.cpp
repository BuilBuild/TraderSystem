/*
 * @Author: LeiJiulong
 * @Date: 2025-01-14 23:08:29
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-14 23:32:52
 * @Description: 将订单推送到消息中心的测试
 */

#include "BaseType.hpp"
#include "json.hpp"
#include "Context.hpp"

#include <zmq.hpp>
#include <thread>
#include <chrono>
#include <iostream>

char CONFIG_PATH[] = "/home/leijiulong/temp/TraderSystem-main/ConfigFileDir/config.json";

int main()
{
    Context *fileContextPtr = Context::getInstance();
    auto fj = fileContextPtr->getJson()["MsgHubCenter"];

    zmq::context_t ctx(1);
    zmq::socket_t pub(ctx, zmq::socket_type::pub);
    
    pub.connect(fj["XSUBConnectAddr"]);
    std::cout << "pub connect " << fj["XSUBConnectAddr"] << std::endl;
    double price = 999.2;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // 发布订单主题
        zmq::message_t topic("OMS");
        pub.send(topic, zmq::send_flags::sndmore);

        // 用json 模拟一个订单消息
        json orderJson;
        orderJson["StrategyName"] = "test";
        orderJson["UserName"] = "admin";
        orderJson["TargetName"] = "au2502";
        orderJson["Price"] = price;
        orderJson["Volume"] = 2;
        orderJson["Direction"] = "1";
        price += 2.5;

        zmq::message_t msg(orderJson.dump());
        pub.send(msg, zmq::send_flags::none);
        
        std::cout << "send " << orderJson["Price"];

    }
    


    
    pub.close();
    ctx.close();

    return 0;
}

