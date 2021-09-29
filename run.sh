generator=gene
mode=0
rounds=50



for filename in  merge merge_bottom_up qsort qsort_rand qsort_medain
do
	for scale in   1000000 10000000
	do
		for threads in 1 2 4 8
		do

		maxn=$scale*2 
		g++ ./$generator.cpp -o $generator -std=c++11 -DMAX_SCALE=$scale -DMAXN=$maxn -DMODE=$mode -fopenmp
		gcc ./$filename.c ./lib.c -o $filename -DMAXN=$maxn -std=c99
		gcc ./"$filename"_multithreads.c ./lib.c -o "$filename"_multithreads -lpthread -fopenmp -DMAXTHREADS=$threads -DMAXN=$maxn -std=c99
		echo "complied"

		for number in $(seq 1 $rounds)  
		do
			echo "Round: $number";
			./$generator
			echo -n "generated "
			./$filename < ./test.in
			echo -n "done "
			./"$filename"_multithreads < ./test.in
  		echo "done."
		done

		mkdir -p ./data/"$scale"
		mv "$filename".txt ./data/"$scale"/"$filename"_"$threads".txt

		done
	done
done
