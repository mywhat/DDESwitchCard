#!/bin/bash
./switchCard.sh -i
cp com.deepin.pkexec.switchCard /usr/share/polkit-1/actions/
cp switchcard.desktop /usr/share/deepin/dde-file-manager/oem-menuextensions/
cp icons/*.svg /usr/share/icons/hicolor/scalable/apps/
