Home=`echo $HOME`

#输出文本
echo "获取Nvidia_BusID..."

NVIDIA_BusID=`lspci | egrep 'VGA|3D' | grep 'NVIDIA' | cut -d ' ' -f 1 | sed -r 's/0?(.)/\1/' | sed -e 's/:0/:/g' -e 's/\./:/g'`

WorkSpace=`pwd`

#写入Xorg配置文件
echo "生成Nvidia所需的Xorg配置..."

echo 'Section "Module"
	Load "modesetting"
EndSection
Section "Device"
	Identifier "nvidia"
	Driver "nvidia"
	BusID "PCI:'$NVIDIA_BusID'"      
	Option "AllowEmptyInitialConfiguration"
EndSection' | sudo tee $WorkSpace/20-nvidia.conf.bak > /dev/null

#写入LightDM启动脚本
echo "生成LightDM启动脚本..."

echo '#!/bin/sh
xrandr --setprovideroutputsource modesetting NVIDIA-0
xrandr --auto
xrandr --dpi 96' | sudo tee $WorkSpace/display_setup.sh.bak > /dev/null

#生成card.conf
nvidia-smi | grep Xorg > /dev/null
if [ $? -ne 0 ]
then
	echo -n "Intel" | sudo tee $WorkSpace/card.conf > /dev/null
else
	echo -n "Nvidia" | sudo tee $WorkSpace/card.conf > /dev/null
fi


#写入内核参数
echo 'options nvidia-drm modeset=1' | sudo tee $WorkSpace/nvidia-graphics-drivers.conf.bak > /dev/null

sudo chmod +x $WorkSpace/display_setup.sh.bak
sudo cp $WorkSpace/20-nvidia.conf.bak /etc/X11/xorg.conf.d
sudo cp $WorkSpace/display_setup.sh.bak /etc/lightdm/
sudo cp $WorkSpace/nvidia-graphics-drivers.conf.bak /etc/modprobe.d/

#安装插件
sudo install -m 755 -p libSwitchVideoCard.so ~/.local/lib/dde-dock/plugins/libSwitchVideoCard.so

#拓展右键菜单
sudo cp SwitchCard.desktop /usr/share/deepin/dde-file-manager/oem-menuextensions/

#移动conf文件和图标到~/.config/switchcard
if [ ! -d $Home/.config/switchcard/ ]
then
	mkdir -p $Home/.config/switchcard/
fi

sudo cp card.conf $Home/.config/switchcard
sudo cp ./icon/*.svg $Home/.config/switchcard

#添加Home路径到Intel和Nvidia脚本
sed -i '2iHome='"$Home"'' Intel.sh
sed -i '2iHome='"$Home"'' Nvidia.sh

if [ ! -d /opt/switchcard/ ]
then
    sudo mkdir -p /opt/switchcard/
fi 

sudo cp *.sh /opt/switchcard/
