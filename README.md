# DDESwitchCard
## 源码编译(需要安装qt编译链和DDE的相关依赖)
cd src && mkdir build

cd build && cmake .. && make -j4

mv libSwitchVideoCard ../..

## 使用
sudo ./setup.sh

## 新增
右键拓展集成为一个子菜单

将图标更改为矢量图svg

集成切换脚本为一个脚本

增加了系统通知，默认为deepin-graphics-driver-manager的图标

增加右键刷新显卡信息

更改为手动重启lightdm，右键插件即可使用

取消外置的card.conf记录信息