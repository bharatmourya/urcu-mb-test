#!/bin/bash

printf "Test case "
cat input
printf "RCU "
./test < input
printf "RW lock " 
./rwlock < input
#printf "Naive lock "
#./mutex < input
#printf "QSBR lock"
#./qsbr < input
