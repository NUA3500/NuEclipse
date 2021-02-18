#!/bin/bash
# Program:
#       This program facilitates the uninstallation for NuEclipse.
# Contributors:
#       Zale Yu - Initial version

set -e -x

INSTALL_PATH=/home/$USER/local
OPENOCD_PATH=$INSTALL_PATH/OpenOCD
PACKS_PATH=$INSTALL_PATH/Packages

if [ -d $OPENOCD_PATH ]; then rm -rf $OPENOCD_PATH; fi
if [ -d $PACKS_PATH ]; then rm -rf $PACKS_PATH; fi

if [ -f /etc/udev/rules.d/10-openocd-nulink.rules ]; then
    sudo rm -f /etc/udev/rules.d/10-openocd-nulink.rules
fi

echo "Done, bye-bye!"
