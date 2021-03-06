#!/usr/bin/env bash

curl -o /opt/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2 -L "https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2?revision=ca0cbf9c-9de2-491c-ac48-898b5bbc0443&la=en&hash=68760A8AE66026BCF99F05AC017A6A50C6FD832A"

cd /opt/
tar xvjf /opt/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2

export PATH=/opt/gcc-arm-none-eabi-10-2020-q4-major/bin/:$PATH