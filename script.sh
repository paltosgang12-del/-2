#!/bin/bash
vlad_tolya_calculate() {
	local numbers=("$@")
	local sum=0
	local count=${#numbers[@]}
	
	for number in "${numbers[@]}"; do
		sum=$(echo "$sum + $number" | bc)
	done
	echo $(echo "scale=2; $sum / $count" | bc)
}

numbers=("$@")
average=$(vlad_tolya_calculate "${numbers[@]}")
echo "Среднее значение: $average"

