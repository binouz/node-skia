#!/bin/sh

echo "{" > config.gypi
echo "\t'variables': {" >> config.gypi
echo "\t\t'egl_platform': \""$1"\"" >> config.gypi
echo "\t}" >> config.gypi
echo "}" >> config.gypi
