# 记录日志
## 1. 项目介绍
在Linux系统中，使用c++运行sh脚本，并读取返回值。
## 2. 使用方法
本项目开发平台信息如下：
- 系统版本：Ubuntu 20.04
- ROS_DISTRO：Noetic
### 2.1 下载
使用git clone下载安装
```shell
git clone https://github.com/zzs-quzz/run_sh.git
```
### 2.2 安装依赖
安装jsoncpp库
```
sudo apt install libjsoncpp-dev
```
### 2.3 运行
1. 构建功能包
```
catkin_make
```
2. 运行测试程序
```
./devel/lib//run_sh/run_sh_ceshi
```
## 3. 其他功能包使用
- 修改CMakeLists.txt：注释add_executable和target_link_libraries
## 4. 作者
- [zzsquzz](https://github.com/zzs-quzz)