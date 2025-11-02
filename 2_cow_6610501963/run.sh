#! /bin/bash

sizes=(50 60 70 80 90 100)

for size in ${sizes[@]}; do
	make run MEM=${size}
	echo
done
