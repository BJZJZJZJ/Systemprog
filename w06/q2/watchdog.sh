#!/bin/bash



while : 
do

if ! pgrep -x "hello.exe" > /dev/null
then
       echo "[shell] Restartring hello.exe..."
	./hello.exe
fi

done

