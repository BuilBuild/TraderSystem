# TraderSystem

## 环境搭建
- 需要安装的模块
  |模块名称|版本|
  |:-:|:-:|
  |boost|1.74.0+ |
  |tbb|2022.0.0|
  |muduo(只需编译base库)|2.0.2|
  |ZeroMQ|4.3.5|

    将ctp动态库移动到lib目录下，在main分支下有其动态库
- cmake 编译
  进入到根目录执行命令
  ```shell
  mkdir build && cd build
  cmake .. && cmake -j8
  ```
  在bin目录下会生成对应的执行文件及相关测试文件

## 配置文件及测试

该系统主要用json来对环境进行配置
- 配置文件,使用时需要将配置文件的注释给删除
    ```json
    {
        // 消息通知接口，ZeroMQ需要读取
        "messageHubBindPort": "tcp://localhost:5555",
        // CTP接口配置，后期可更具不同的柜台进行配置
        "CTP_API" :{
            "gTradeFrontAddr": "tcp://180.168.146.187:10212",
            // 以下为账户信息，和订阅的标的
            "BrokerID": "***",
            "UserID": "***",
            "PassWord": "***",
            "InstrumentID": [
                "cu2502",
                "al2502",
                "zn2502",
                "pb2502",
                "au2502",
                "ag2502",
                "rb2505",
                "wr2505",
                "fu2503",
                "ru2505",
                "bu2502",
                "hc2505",
                "ni2502",
                "sn2502",
                "sp2503",
                "ss2502",
                "ao2502",
                "br2502"
            ]
        },
        // 订单执行器系统配置
        "ExecutionManage":{
            "CTPTrader":{
            "gTradeFrontAddr": "tcp://180.168.146.187:10202",
            "BrokerID": "9999",
            "UserID": "***",
            "PassWord": "***"
            }
        },
        // 订单管理系统配置
        "OMS":{
            "OMS_ID": 1,
            // 推送接口
            "SubAddr": "tcp://localhost:5558"
        },
        // 消息中心接口配置（ZeroMQ XSUB-XPUB模式）
        "MsgHubCenter":{
            "XSUBBindAddr": "tcp://*:9898",
            "XSUBConnectAddr": "tcp://localhost:9898",
            "XPUBBindAddr": "tcp://*:5558"
        }
        

    }
    ```
- 示例代码
  当运行实例的时候需要添加一个全局变量，即配置文件的路径，后期可以通过命令行读入
    ```cpp
    #include <iostream>
    #include "DataCenter.h"
    #include "DataApi.h"
    #include "Strategy.h"
    #include "CtpApi.h"

    #include <muduo/base/Logging.h>
    #include <iostream>
    #include <thread>
    #include <chrono>
    #include <string>


    DataApi* DATA_API = nullptr;

    char CONFIG_PATH[] = "/home/leijiulong/temp/TraderSystem-main/ConfigFileDir/config.json";
    int main()
    {
    #ifdef LOG_DEBUG
        muduo::Logger::Logger::setLogLevel(muduo::Logger::LogLevel::DEBUG);
    #endif

        DATA_API = new DataApi(new CtpApi());
        auto t = DataCenter::getInstance();
        Strategy s1 = Strategy("s1",t);
        Strategy s2 = Strategy("s2",t);
        std::cout << "hello test_test_get" << std::endl;
        TargetOBJ a{"hello"};
        TargetOBJ targetList[] = {
            {"t1"}, {"t2"},{"t2"}, {"t3"}, {"target_7"}
        };
        s1.subScribeTargetOne(a);
        s1.subScribeTargets(targetList, 5);
        getchar();
        return 0; 
    }
    ``` 
    订单执行测试
    ```cpp
    #include "OrderManager.h"
    #include "ExecutionSystem.h"
    #include "ExecutionCtpTrader.h"

    #include <iostream>

    char CONFIG_PATH[] = "/home/leijiulong/temp/TraderSystem-main/ConfigFileDir/config.json";

    int main()
    {
        ExecutionCtpTrader ctpTrader;
        ExecutionSystem t(&ctpTrader);
        OMS ms(&t);
        getchar();
        t.getTradingInfo();
        getchar();
        return 0;
    }

    ```
