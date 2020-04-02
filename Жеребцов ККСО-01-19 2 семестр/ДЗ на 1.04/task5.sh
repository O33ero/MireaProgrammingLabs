#!/bin/bash

#Жеребцов ККСО-01-19 Архивирование всех файлов в директории

for file in $(ls -1)
do
	if [[ $file != "task5.sh" ]]
	then
	gzip -k $file
	fi
done


