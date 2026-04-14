#include "run_sh/run_sh.h"

int main(int argc, char **argv)
{
    std::string sh_path = "/home/zzs/catkin_ws/src/run_sh/scripts/ceshi.sh"; // 需修改
    std::string result = exce_sh(sh_path.c_str());
    if (parse_result(result))
    {
        printf("测试成功\n");
    }
    return 0;
}