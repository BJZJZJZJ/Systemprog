#!/bin/bash

echo "1.Create a file"
echo "2.Create a directory"
echo "3.Remove a file"
echo "4.Remove a directory"
echo "Enter: " 

read n

case $n in
	1 | 3) 
		echo "Enter filename: "
		read file
		if [ $n -eq 1 ]
			then touch $file
		else rm $file
		fi;;
	2 | 4) 
		echo "Enter directory name: "
		read dir
		if [ $n -eq 2 ]
			then mkdir dir
		else rmdir dir
		fi;;
	*) echo "Quit";;
esac
