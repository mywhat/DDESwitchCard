# DDESwitchCard
## 源码编译(需要安装qt编译链和DDE的相关依赖)
cd src && mkdir build

cd build && cmake .. && make -j4

mv libSwitchVideoCard ../..

## 使用
./setup.sh
