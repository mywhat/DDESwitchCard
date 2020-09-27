# DDESwitchCard
## 源码编译(需要安装qt编译链和DDE的相关依赖)
cd src && mkdir build

cd build && cmake .. && make -j4

mv libSwitchVideoCard ../..

## 使用
./setup.sh

## 新增
右键拓展集成为一个子菜单

将图标更改为矢量图svg

添加认证时的提示框弹出内容，将com.deepin.pkexec.switchCard.policy添加到/usr/share/polkit-1/actions即可
