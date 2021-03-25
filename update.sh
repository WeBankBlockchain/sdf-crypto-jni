#!/bin/bash
if [ $1 = "up" ]
then
  ./gradlew goJF
  git add .
  git commit -m "fix bug"
  git push origin master
elif [ $1 = "down" ]; then
  git fetch --all
  git reset --hard origin/master
elif [ $1 = "run" ]; then
  ./gradlew goJF
  ./gradlew build
  cd dist
  java -cp "apps/*" com.webank.wedpr.crypto.hsm.Main
elif [ $1 = "swig" ]; then
  cd src/main/resources
  swig -c++ -java -package com.webank.wedpr.crypto.hsm.sdf -outdir ./ -I SDF.i
elif [ $1 = "g++" ]; then
  cd src/main/resources
  g++ -fpic -shared -o sdf-crypto_arm.so SDF_wrap.cxx -I /usr/lib/jvm/jdk-11.0.10/include/ -I /usr/lib/jvm/jdk-11.0.10/include/linux/ libsdf-crypto_arm.so -L.
else
  echo "./update.sh [up/down/run/swig]"
fi

