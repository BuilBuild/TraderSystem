/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 14:58:24
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-06 16:11:42
 * @Description: 
 */
#include "MsgHub.h"

#include <iostream>

char CONFIG_PATH[] = "/home/leijiulong/git_project/TraderSystem/ConfigFileDir/config.json";

int main()
{
    std::cout << "msg hub test " << std::endl;
    MessagingHub t;
    getchar();
    return 0;
}