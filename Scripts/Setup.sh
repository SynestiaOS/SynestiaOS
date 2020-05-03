#!bin/sh

before(){
    brew install wget
    brew install tar
}

downloadArmToolChain(){
    echo "\033[32m Downloading ArmGCCToolChain... \033[0m" 
    wget -c https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-mac.tar.bz2
    echo "\033[32m ArmGCCToolChain Downloaded! \033[0m" 
    mv gcc-arm-none-eabi-9-2019-q4-major-mac.tar.bz2 ../Tools/
    cd ../Tools
}

setUpArmGccToolChain(){
    echo "\033[32m Unpackaging ArmGCCToolChain... \033[0m" 
    tar -jxvf gcc-arm-none-eabi-9-2019-q4-major-mac.tar.bz2
    echo "\033[32m ArmGCCToolChain Unpackaged! \033[0m" 

    ARM_TOOL_CHAIN_HOME=`pwd`/gcc-arm-none-eabi-9-2019-q4-major/bin

    echo "export ARM_TOOL_CHAIN_HOME="$ARM_TOOL_CHAIN_HOME >> ~/.zshrc
    echo "export PATH=\$PATH:\$ARM_TOOL_CHAIN_HOME" >> ~/.zshrc

    echo "\033[32m Setting up Environment Variable! \033[0m" 
    echo "\033[32m Please copy two line below, and paste them into ~/.zshrc or ~/.bashrc, and then execute source ~/.zshrc \033[0m" 
    echo ""
    echo "\033[35m export ARM_TOOL_CHAIN_HOME=$ARM_TOOL_CHAIN_HOME \033[0m" 
    echo "\033[35m export PATH=\$PATH:\$ARM_TOOL_CHAIN_HOME \033[0m" 
    echo ""
    source ~/.zshrc
    cd ../Srcipts
}

installQemuVirtualMachine(){
    brew install qemu
}

# download arm gcc tool chain from develoepr.arm.com
downloadArmToolChain

# unpackage arm gcc toolchain and set up environment variable
setUpArmGccToolChain

# install qemu-system-i386
installQemuVirtualMachine



