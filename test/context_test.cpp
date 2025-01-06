/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 14:59:24
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 21:03:04
 * @Description: 
 */
#include "Context.hpp"

#include <iostream>

char CONFIG_PATH[] = "/home/leijiulong/temp/TraderSystem-main/ConfigFileDir/config.json";
int main()
{
    std::cout << "context_test" << std::endl;
    Context* context = Context::getInstance();
    std::cout << "message hub port bind " << context->messageHubBindPort() << std::endl;
    return 0;
}