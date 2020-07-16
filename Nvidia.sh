User=`echo $USER`
WORKSPACE=`pwd`

#提示文本
echo '即将切换至NVIDIA显卡，请输入登录密码，回车后会自动注销。在此之前，请保存好当前的工作。'

xorg_file=/etc/X11/xorg.conf.d/20-nvidia.conf.bak
drivers_file=/etc/modprobe.d/nvidia-graphics-drivers.conf.bak
display_path=/etc/lightdm/display_setup.sh.bak

#测试文件是否存在
if [ ! -f $xorg_file ] 
then
    sudo cp $WORKSPACE/20-nvidia.conf.bak /etc/X11/xorg.conf.d/
fi

if [ ! -f $drivers_file ] 
then
    sudo cp $WORKSPACE/nvidia-graphics-drivers.conf.bak /etc/modprobe.d/
fi

if [ ! -f $display_path ] 
then
    sudo cp $WORKSPACE/display_setup.sh.bak /etc/lightdm/
fi

sudo mv $xorg_file /etc/X11/xorg.conf.d/20-nvidia.conf
sudo mv $drivers_file /etc/modprobe.d/nvidia-graphics-drivers.conf
sudo mv $display_path /etc/lightdm/display_setup.sh

#修改LightDM配置文件
sudo sed -i 's$#display-setup-script=$display-setup-script=/etc/lightdm/display_setup.sh$g' /etc/lightdm/lightdm.conf

#更新conf
echo -n 'Nvidia' | sudo tee /home/$User/.config/switchcard/card.conf > /dev/null

#重启LightDM服务，注销即可切换
sudo service lightdm restart
