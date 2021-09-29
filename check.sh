filename=merge
threads=4
generator=gene
scale=10
maxn=20000


g++ ./$generator.cpp -o $generator -std=c++11 -DMAX_SCALE=$scale  -DMAXN=$maxn -fopenmp
gcc ./$filename.c ./lib.c -o $filename -D__CHECK 
gcc ./"$filename"_dmultithreads.c ./lib.c -o "$filename"_dmultithreads -lpthread -DMAXTHREADS=$threads -D__CHECK  -fopenmp -std=c99

while true; do
	./$generator
	./$filename < ./test.in  >  $filename.out
	./"$filename"_dmultithreads < ./test.in > "$filename"_multithreads.out
if (diff -bB test.out "$filename".out) && (diff -bB test.out "$filename"_multithreads.out);then
printf AC
else 
echo WA
exit 0
fi
done
 
