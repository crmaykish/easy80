#!/bin/sh

UNITY_REPO="https://github.com/ThrowTheSwitch/Unity.git"

mkdir -p ./libs
cd ./libs

echo "Fetching Unity..."
git clone $UNITY_REPO
echo "Unity is ready!"

cd ..