#!/bin/bash

###
 # @Description  : Switch Card
 # @Author       : Chan
 # @Date         : 2020-10-06 09:55:12
 # @LastEditor   : Chan
 # @LastEditTime : 2020-10-07 23:51:32
### 

readonly helpString="
-h or --help 获取命令帮助\n \
\b-s or --switch 进行显卡的切换，可选参数为intel,nvidia或者hybrid\n \
\b-i or --init 进行初始化的设置\n \
\b-r or --remove 进行插件的移除
"

driversPath=/etc/modprobe.d
displayPath=/etc/lightdm

xorgConfPath=/etc/X11
lightdmConfPath=/etc/lightdm

Nvidia_BusID=`lspci | egrep 'VGA|3D' | grep 'NVIDIA' | cut -d ' ' -f 1 | sed -r 's/0?(.)/\1/' | sed -e 's/:0/:/g' -e 's/\./:/g'`
Intel_BusID=`lspci | egrep 'VGA|3D' | grep 'Intel' | cut -d ' ' -f 1 | sed -r 's/0?(.)/\1/' | sed -e 's/:0/:/g' -e 's/\./:/g'`

function switchCard() {
    if [ ! -z $1 ] 
    then 
        echo -e "Ready to switch card......\nRemember to backup your data first!"
    else
        echo -e "Error!Lack of variable......"
        echo -e $helpString
        return -1
    fi
    
    case $1 in
    "intel" | "Intel" | "INTEL")
        mv $xorgConfPath/xorg.conf $xorgConfPath/xorg.conf.bak
        mv $driversPath/nvidia-graphics-drivers.conf $driversPath/nvidia-graphics-drivers.conf.bak
        mv $displayPath/display_setup.sh $displayPath/display_setup.sh.bak
        sed -i 's$display-setup-script=/etc/lightdm/display_setup.sh$#display-setup-script=$g' $lightdmConfPath/lightdm.conf;;

    "nvidia" | "Nvidia" | "NVIDIA")
        mv $xorgConfPath/xorg.conf.bak $xorgConfPath/xorg.conf
        sed -i 's$Screen      0  .* 0 0$Screen      0  "DGPU" 0 0$g' $xorgConfPath/xorg.conf
        sed -i 's$Option         "AllowNVIDIAGPUScreens"$    #Option         "AllowNVIDIAGPUScreens"$g' $xorgConfPath/xorg.conf
        mv $driversPath/nvidia-graphics-drivers.conf.bak $driversPath/nvidia-graphics-drivers.conf
        mv $displayPath/display_setup.sh.bak $displayPath/display_setup.sh
        sed -i 's$#display-setup-script=$display-setup-script=/etc/lightdm/display_setup.sh$g' $lightdmConfPath/lightdm.conf;;
    
    "hybrid" | "Hybrid" | "HYBRID")
        mv $xorgConfPath/xorg.conf.bak $xorgConfPath/xorg.conf
        sed -i 's$Screen      0  .* 0 0$Screen      0  "IGPU" 0 0$g' $xorgConfPath/xorg.conf
        sed -i 's$#.*Option         "AllowNVIDIAGPUScreens"$    Option         "AllowNVIDIAGPUScreens"$g' $xorgConfPath/xorg.conf
        mv $driversPath/nvidia-graphics-drivers.conf $driversPath/nvidia-graphics-drivers.conf.bak
        mv $displayPath/display_setup.sh $displayPath/display_setup.sh.bak
        sed -i 's$display-setup-script=/etc/lightdm/display_setup.sh$#display-setup-script=$g' $lightdmConfPath/lightdm.conf;;

    *)
    echo -e "Error parse variable '$1'!"
    return -1
    esac
    
    return 0
}

function initEnv() {
    echo -e "Init Environment......\nDefault IntelCard"
    cp xorg.conf $xorgConfPath/xorg.conf.bak
    cp display_setup.sh $displayPath/display_setup.sh.bak
    cp nvidia-graphics-drivers.conf $driversPath/nvidia-graphics-drivers.conf.bak
    sed -i 's$.*"PCI:Nvidia_BusID"$    BusID          "PCI:'"$Nvidia_BusID"'"$g' $xorgConfPath/xorg.conf.bak
    sed -i 's$.*"PCI:Intel_BusID"$    BusID          "PCI:'"$Intel_BusID"'"$g' $xorgConfPath/xorg.conf.bak
    chmod +x $displayPath/display_setup.sh.bak
    if [ $? -ne 0 ]
    then
        echo -e "Error init......\nPlease try to remove all config"
        return -1
    fi

}

function removeAll() {
    echo "Remove all files and Reset environment......"
    rm $xorgConfPath/xorg.conf $xorgConfPath/xorg.conf.bak >> /dev/null
    rm $displayPath/display_setup.sh $displayPath/display_setup.sh.bak >> /dev/null
    rm $driversPath/nvidia-graphics-drivers.conf $driversPath/nvidia-graphics-drivers.conf.bak >> /dev/null
    sed -i 's$display-setup-script=/etc/lightdm/display_setup.sh$#display-setup-script=$g' $lightdmConfPath/lightdm.conf
}

function checkCard() {
    glxinfo | grep "OpenGL vendor" | grep "NVIDIA" > /dev/null

    if [ $? -ne 0 ]
    then
        prime-run glxinfo | grep "OpenGL vendor" | grep "NVIDIA" > /dev/null
        if [ $? -ne 0 ]
        then
            echo "Intel"
        else
            echo "Prime"
        fi
    else
        echo "Nvidia"
    fi
}

case $1 in 
"-h" | "--help")
    echo -e $helpString;;

"-s" | "--switch")
    switchCard $2
    if [ $? -ne 0 ] 
    then
        echo -e "Error Switch Card '$2'!"
    else
        echo -e "Success"
	notify-send --app-name=switchcard --icon=deepin-graphics-driver-manager 请重启lightdm使$2显卡切换生效 	
    fi;;

"-i" | "--init")
    initEnv;;

"-r" | "--remove")
    removeAll;;

"-c" | "--checkcard")
    checkCard;;

*)
echo -e "Error parse variable '$1'!"
esac
    
