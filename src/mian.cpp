/*
 * @Author: LeiJiulong
 * @Date: 2025-01-03 13:15:41
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-03 13:24:19
 * @Description: 
 */

#include <iostream>

#include "json.hpp"

 using json = nlohmann::json;

int main()
{
    std::cout << "hello "  << std::endl;
    auto j = json::parse("{\"id\": 1}");
    std::cout << "id: " << j["id"] << std::endl;
    return 0;
}
