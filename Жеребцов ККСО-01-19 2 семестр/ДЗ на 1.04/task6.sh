#!/bin/bash

#Жеребцов ККСО-01-19 Запуск файла .c

function is_found 
{
	for file in $(ls -1)
	do
		if [[ $file == $1 ]]
		then
			echo 0	
		fi
 	done
	
	echo 1	
}


echo "Searching file..."

if [[ $(is_found $1) == 1 ]]
then
	echo "File not found."
else
	echo "File is found. Compiled..." 
	gcc $1
	echo "File compilated. Out of file:" 
       ./a.out
       	echo "Script finish working."
fi

