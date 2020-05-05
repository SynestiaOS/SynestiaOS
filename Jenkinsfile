pipeline {
    agent any

    stages {
        stage('Clean'){
            steps {
                echo 'Cleaning...'
                sh 'make clean'
            }
        }
        stage('Build-ARM32') {
            steps {
                echo 'Building ARM32...'
                sh 'make ARCH=arm'
            }
        }
         stage('Build-ARM64') {
            steps {
                echo 'Building ARM64...'
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