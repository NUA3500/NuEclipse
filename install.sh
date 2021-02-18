#!/bin/bash
# Program:
#       This program facilitates the installation for NuEclipse.
# Contributors:
#       Zale Yu - Initial version

set -e -x

if [ "`whoami`" == "root" ]; then
    echo "Please do not use a root privilege to run this script!"	
    exit 1
fi

if [ "`uname -m`" != "x86_64" ]; then
    echo "Sorry! This tool only runs on the 64-bit Linux."	
    exit 1
fi

INSTALL_PATH=/home/$USER/local
OPENOCD_PATH=$INSTALL_PATH/OpenOCD
PACKS_PATH=$INSTALL_PATH/Packages
GCC_VERSION=gcc-arm-none-eabi-6-2017-q1-update
GCC_PATH=$INSTALL_PATH/$GCC_VERSION

DEPENDENCY_LIB="default-jre"
#echo "Installing dependecy library.. $DEPENDENCY_LIB"
#sudo apt-get install  $DEPENDENCY_LIB

if [ ! -d $INSTALL_PATH ]; then mkdir -p $INSTALL_PATH; fi

if [ -f $GCC_PATH/bin/arm-none-eabi-gcc ]; then
    echo "The GNU ARM Embedded Toolchain has existed."
else
    echo "Installing the GNU ARM Embedded Toolchain..."
    tar -xf "./Others/"$GCC_VERSION"-linux.tar.bz2" -C $INSTALL_PATH
    echo "Just finished installing the GNU ARM Embedded Toolchain."
fi

$GCC_PATH/bin/arm-none-eabi-gcc -v

if [ -f $OPENOCD_PATH/bin/openocd ]; then
    echo "Removing the previous OpenOCD..."
    $OPENOCD_PATH/bin/openocd -v
    rm -r $OPENOCD_PATH/bin/openocd
fi

cp -afr ./eclipse/OpenOCD $INSTALL_PATH
echo "Just finished installing the OpenOCD."
$OPENOCD_PATH/bin/openocd -v

if [ -f $PACKS_PATH/Nuvoton ]; then
    echo "Removing the previous Nuvoton Packs..."
    rm -r $PACKS_PATH/Nuvoton/
fi

cp -afr ./eclipse/Packages $INSTALL_PATH
echo "Just finished installing the Nuvoton Packs."


set +e

#get the USB permission by adding udev rules for Nu-Link
sudo useradd -G plugdev $USER
if [ ! -f /etc/udev/rules.d/10-openocd-nulink.rules ]; then
    sudo cp -af ./Others/10-openocd-nulink.rules /etc/udev/rules.d/
    echo "Just finished adding 10-openocd-nulink.rules."
fi

xdg-open "./UserManual/UM_NuEclipse_EN.pdf"
xdg-open "http://github.com/OpenNuvoton"

echo "Done, bye-bye!"
