#include <iostream>
#include <memory>
#include <cstdio>
#include <sstream>
#include <array>
#include <jsoncpp/json/json.h>
#include <run_sh/run_sh.h>

std::string exce_sh(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    // 执行sh
    if (!pipe)
    {
        printf("执行sh失败");
        throw std::runtime_error("popen() failed!");
    }
    // 读取返回内容，一般为json格式
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

bool parse_result(std::string result)
{
    // 将string转为json
    Json::Value root;
    Json::CharReaderBuilder readerBuilder;
    std::string errs;
    std::istringstream iss(result);
    if (!Json::parseFromStream(readerBuilder, iss, &root, &errs))
    {
        printf("JSON parse error: %s", errs.c_str());
        return false;
    }
    // 处理json
    if (root.isMember("message") && !root["message"].isNull())
    {
        std::string message = root["message"].asString();
        printf("message:%s", message.c_str());
    }
    return true;
}