# Prepare Environment
## Clion
[Clion](https://www.jetbrains.com/clion) is recommend to used as our development environment, and use docker to build the kernel.
under this **Docker** dir, run following command to setup dev environment
```
docker-compose up -d dev-prebuilt
```
within the docker container, we setup the ssh environment, and we can connect to the container through ssh.
```
docker-compose exec dev-prebuilt /bin/bash
#> cd Build
#> cmake .. && make
```
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
docker-compose up -d dev-prebuilt
```

# code formatting
under this project dir, run following command to format the code 
```
docker-compose run dev-prebuilt bash run-clang-foramt.sh
``` 
# Build, Run and Debug
within the docker container, under the Build dir, run following command to build kernel
```
cmake .. && make VERBOSE=1
```
if you are using mac, specify the cross compile toolchain in CMake/ToolchainMacArm.cmake, 
and specify the toolchain file location
```
cmake -DCMAKE_TOOLCHAIN_FILE=${PATH_TO_THIS_PROJECT}/SynestiaOS/CMake/ToolchainMacArm.cmake .. && make VERBOSE=1
```
To run kernel, you can find the kernel image under Build/
```
qemu-system-arm -M raspi2 -kernel bin/Kernel.img -nographic -serial mon:stdio      #for raspi2 and arm32
qemu-system-aarch64 -M raspi3 -kernel bin/Kernel.img -nographic -serial mon:stdio  #for raspi3 and arm64
```
To run kernel unit tests, you can find the kernel unit tests image under Build/
```
qemu-system-arm -M raspi2 -kernel bin/KernelUnitTests.img -nographic -serial mon:stdio      #for raspi2 and arm32
qemu-system-aarch64 -M raspi3 -kernel bin/KernelUnitTests.img -nographic -serial mon:stdio  #for raspi3 and arm64
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
