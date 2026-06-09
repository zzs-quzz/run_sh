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
        printf("message:%s\n", message.c_str());
    }
    return true;
}

bool parse_get_point(std::string result, executing_point &point)
{
    Json::Value root;
    Json::CharReaderBuilder readerBuilder;
    std::string errs;
    std::istringstream iss(result);
    if (!Json::parseFromStream(readerBuilder, iss, &root, &errs))
    {
        printf("JSON parse error: %s\n", errs.c_str());
        return false;
    }

    const Json::Value &data = root["data"];

    if (data["executing"].asBool())
    {
        std::string message = root["message"].asString();
        printf("message:%s\n", message.c_str());
        if (data.isMember("point") && !data["point"].isNull() && data["point"].isObject())
        {
            const Json::Value &pointJson = data["point"];
            point.posX = pointJson["posX"].asFloat();
            point.posY = pointJson["posY"].asFloat();
            point.posZ = pointJson["posZ"].asFloat();
            point.angleyaw = pointJson["angleyaw"].asFloat();
            point.point_name = pointJson["name"].asString();
            point.gait = pointJson["gait"].asInt();
            point.navMode = pointJson["navMode"].asInt();
            point.is_executing = pointJson["isExecuting"].asBool();
            printf("巡检点位获取成功。posX:%.2f,posY:%.2f,posZ:%.2f,angleyaw:%.2f,gait:%d,navMode:%d,is_executing:%s,point_name:%s\n",
                   point.posX, point.posY, point.posZ, point.angleyaw, point.gait, point.navMode, point.is_executing ? "true" : "false", point.point_name.c_str());
            return true;
        }
        else
        {
            printf("没有point成员或point为null\n");
            return false;
        }
    }
    else
    {
        printf("没有执行任务\n");
        return false;
    }
}

bool parse_obstacle(std::string result, float time)
{
    Json::Value root;
    Json::CharReaderBuilder readerBuilder;
    std::string errs;
    std::istringstream iss(result);
    if (!Json::parseFromStream(readerBuilder, iss, &root, &errs))
    {
        printf("JSON parse error: %s\n", errs.c_str());
        return false;
    }

    std::string message = root["message"].asString();
    printf("message:%s,时间为：%.2f\n", message.c_str(), time);
    bool success = root["success"].asBool();
    return success;
}