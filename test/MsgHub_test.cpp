/*
 * @Author: LeiJiulong
 * @Date: 2025-01-11 19:49:27
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-11 19:54:19
 * @Description: 
 */
#include"MsgHub.h"

char CONFIG_PATH[] = "/home/leijiulong/temp/TraderSystem-main/ConfigFileDir/config.json";

int main()
{
    MessagingHub m;
    m.start();
    return 0;
}