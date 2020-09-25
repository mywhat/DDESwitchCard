Home=

#提示文本
echo '即将切换至Intel显卡，请输入登录密码，回车后会自动注销。在此之前，请保存好当前的工作。'

xorg_path=/etc/X11/xorg.conf.d/
drivers_path=/etc/modprobe.d/
display_path=/etc/lightdm/

#重命名配置文件
sudo mv $xorg_path/20-nvidia.conf $xorg_path/20-nvidia.conf.bak
sudo mv $drivers_path/nvidia-graphics-drivers.conf $drivers_path/nvidia-graphics-drivers.conf.bak
sudo mv $display_path/display_setup.sh  $diplay_path/display_setup.sh.bak

#恢复LightDM配置文件
sudo sed -i 's$display-setup-script=/etc/lightdm/display_setup.sh$#display-setup-script=$g' /etc/lightdm/lightdm.conf

#更新conf
echo -n 'Intel' | sudo tee $Home/.config/switchcard/card.conf > /dev/null

#重启LightDM服务，注销即可切换
sudo service lightdm restart

