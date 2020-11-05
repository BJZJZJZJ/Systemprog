#!/bin/bash

echo "Enter the Number"
read n

x=0  
y=1  
i=2  # Loop Counter

# if n < 1 then exit
if [ $n -lt 1 ] 
then
	echo "Can't Calc!" 
	exit 0
fi

# Fibonacci Calc
while [ $i -lt $n ]
	do
		i=`expr $i + 1`  # Loop Counter
		z=`expr $x + $y` 
		x=$y
		y=$z
	done

res=`expr $x + $y`
echo "Result : $res"
exit 0
