for ((i = 0; i < $1 + 1; i += 1))
do
    for ((j = 0; j < $2; j += 1))
    do
	../lemipc `pwd` $i &
    done
done
