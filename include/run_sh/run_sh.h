#pragma once
#include <string>

struct executing_point
{
    float posX, posY, posZ, angleyaw;
    int gait;
    int navMode;
    int poseture;
    std::string point_name;
    bool is_executing;
};

std::string exce_sh(const char *cmd);
bool parse_result(std::string result);
bool parse_get_point(std::string result, executing_point &point);
bool parse_obstacle(std::string result, float time);