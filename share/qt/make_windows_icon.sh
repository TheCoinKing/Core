#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/coinking.png
ICON_DST=../../src/qt/res/icons/coinking.ico
convert ${ICON_SRC} -resize 16x16 coinking-16.png
convert ${ICON_SRC} -resize 32x32 coinking-32.png
convert ${ICON_SRC} -resize 48x48 coinking-48.png
convert coinking-48.png coinking-32.png coinking-16.png ${ICON_DST}

