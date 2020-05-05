pipeline {
  agent any
  stages {
    stage('Clean') {
      steps {
        echo 'Cleaning...'
        sh 'export PATH=$PATH:/home/ubuntu/SynestiaOS/gcc-arm-none-eabi-9-2019-q4-major/bin'
        sh 'make clean'
      }
    }

    stage('Build-ARM32') {
      steps {
        echo 'Building ARM32...'
        sh 'make clean'
        sh 'make ARCH=arm'
      }
    }

    stage('Build-ARM64') {
      steps {
        echo 'Building ARM64...'
        sh 'make clean'
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