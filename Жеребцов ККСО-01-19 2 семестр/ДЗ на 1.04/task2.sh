#!/bin/bash

#Жеребцов ККСО-01-19 Поиск директорий кратных 5

for file in $(ls -1)
do	
	#Удаление через маску
	if [[ (($file == "dir"*"0")) || (($file == "dir"*"5"))]]
	then
       	echo "i removed $file"
	rm -d $file
	fi
done


