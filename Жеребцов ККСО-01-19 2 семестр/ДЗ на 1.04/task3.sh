#!/bin/bash

#Жеребцов ККСО-01-19 Сумма всех txt

touch sum_out.txt

for txt in $(ls -1)
do
	if [[ (($txt == *".txt")) && (($txt != "sum_out.txt")) ]]
	then
	cat $txt >> sum_out.txt
	fi	
done


