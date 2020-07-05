# SynestiaOS
## An Open Source, standards-based software platform for IOT devices, including smartwatch, TVs and automotive infotainment platforms.

# Prepare Environment
## Clion
[Clion](https://www.jetbrains.com/clion) is recommend to used as our development environment, add use docker to build the kernel.
under this **Build** dir, run following command to setup dev environment
```
docker-compose up -d dev
```
within the docker container, we setup the ssh environment, and we can connect to the container through ssh.
within Clion, Settings->Build,Execution,Deployment->Toolchain, click add a remote host, 
and input the credentials, user: root, password: password. and it's done.

## for linux:
``` bash
sudo bash Scripts/SetupLinux.sh
```
## for windows:

## for docker:
under this project dir, run following command to setup dev environment
```
docker-compose up -d dev
```

# code formatting
under this project dir, run following command to format the code 
```
docker-compose run dev bash run-clang-foramt.sh
``` 
# Build, Run and Debug
within the docker container, under the Build dir, run following command to build kernel
```
cmake .. && make VERBOSE=1
```
if you are using mac, specify the cross compile toolchain in CMake/ToolchainArmMac.cmake, 
and specify the toolchain file location
```
cmake -DCMAKE_TOOLCHAIN_FILE=${PATH_TO_THIS_PROJECT}/SynestiaOS/CMake/ToolchainArmMac.cmake .. && make VERBOSE=1
```
To run kernel, you can find the kernel image under Build/Kernel/Arch
```
qemu-system-arm -M raspi2 -kernel Kernel.img -nographic -serial mon:stdio      #for raspi2 and arm32
qemu-system-aarch64 -M raspi3 -kernel Kernel.img -nographic -serial mon:stdio  #for raspi3 and arm64
```
To clean workspace:
```
make clean
```
To debug kernel, arm32 for instance:
openup terminal 1:
```
qemu-system-arm -M raspi2 -kernel Kernel.img -s -S -nographic
```
openup terminal 2:
```
gdb-multiarch Kernel.img
(gdb) target remote :1234
(gdb) display/i $pc
(gdb) break _start
(gdb) c
(gdb) si
```
# Project Management
[JIRA](https://synestiaos.atlassian.net/)

# Pipeline
[Jenkins](http://ci.synestiaos.org/)

# Resource
[Makefile](https://wiki.ubuntu.org.cn/%E8%B7%9F%E6%88%91%E4%B8%80%E8%B5%B7%E5%86%99Makefile:%E6%A6%82%E8%BF%B0)
