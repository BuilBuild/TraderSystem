/*
 * @Author: LeiJiulong
 * @Date: 2025-01-17 11:10:59
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-17 11:38:36
 * @Description: 
 */
#include <fstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>



using CSVHeader = std::vector<std::string>;
using DataSource = std::unordered_map<std::string, std::vector<std::Any>>;

class CSV
{
public:

    CSV() = delete;
    explicit CSV(std::string filePath);
    ~CSV();

    CSV& operator = (const CSV&) = delete;
    CSV(const CSV &) = delete;
    
private:

private:
    // 读写文件的描述符
    std::unique_ptr<std::ofstream> fileFd_;
    // 文件头
    CSVHeader header_;
};


