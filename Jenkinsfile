pipeline {
    agent any

    stages {
        stage('Clean'){
            steps {
                echo 'Cleaning...'
                 make clean
            }
        }
        stage('Build-ARM32') {
            steps {
                echo 'Building ARM32...'
                make ARCH=arm
            }
        }
         stage('Build-ARM64') {
            steps {
                echo 'Building ARM64...'
                make ARCH=arm64
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