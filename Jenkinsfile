pipeline {
  agent any
  stages {
    stage('Clean') {
      steps {
        echo 'Cleaning...'
        sh 'export ARM_TOOL_CHAIN_HOME=/home/ubuntu/SynestiaOS/gcc-arm-none-eabi-9-2019-q4-major/bin'
        sh 'export PATH=$PATH:$ARM_TOOL_CHAIN_HOME'
        sh 'make clean'
      }
    }

    stage('Build-ARM32') {
      steps {
        echo 'Building ARM32...'
        sh 'export ARM_TOOL_CHAIN_HOME=/home/ubuntu/SynestiaOS/gcc-arm-none-eabi-9-2019-q4-major/bin'
        sh 'export PATH=$PATH:$ARM_TOOL_CHAIN_HOME'
        sh 'make ARCH=arm'
      }
    }

    stage('Build-ARM64') {
      steps {
        echo 'Building ARM64...'
        sh 'export ARM_TOOL_CHAIN_HOME=/home/ubuntu/SynestiaOS/gcc-arm-none-eabi-9-2019-q4-major/bin'
        sh 'export PATH=$PATH:$ARM_TOOL_CHAIN_HOME'
        sh 'make ARCH=arm64'
      }
    }

    stage('Test') {
      steps {
        echo 'Testing...'
      }
    }

    stage('Release') {
      steps {
        echo 'Releasing...'
      }
    }

  }
}