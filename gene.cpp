#include<bits/stdc++.h>
#include<omp.h>
#include"testrc.h"
#ifndef MAX_SCALE 
#define MAX_SCALE 10000000
#endif
int a[MAXN];



/* 5 generator mode:
default:	unform int -MAX-MAX,data scale MAX-MAX*2
sorted:		default generator,sorted
reverse:	default generator,sorted & reverse
repeated:	large repeated data
sp:				hack the quicksort,like make the possible pivot be the smallest one
medain:		special constructor to hack conventional medain3 pivot  
*/


#ifndef MODE
#define MODE __default_
#endif


int main(){
	std::mt19937_64 generator;  //Mersenne Twister 19937 64bit generator
	#if MODE==__repeated_
	std::uniform_int_distribution<int> distribution(-100,100);
	#else
	std::uniform_int_distribution<int> distribution(-MAX_SCALE,MAX_SCALE);
	#endif
	std::uniform_int_distribution<int> data_scale(MAX_SCALE,MAX_SCALE<<1);

	generator.seed(time(0));
	memset(a,0,sizeof(a));
	int n = data_scale(generator);
	#if MODE==__medain_
	while (n & 3) n++;
	int k=n>>1;
	#pragma omp parallel for
	for (int i=0;i<k;i+=2){
		a[i]=(i>>1)+1;
		a[i+1]=a[i]+k;
	}
	#pragma omp parallel for
	for (int i=0;i<k;i++) a[i+k]=(i<<1)+2;
	#else
	generator.seed(time(0));
	#pragma omp parallel for
	for (int i=0;i<n;++i) a[i] = distribution(generator); //defaultmode
	#endif	

	#if MODE==__sorted_
	std::sort(a,a+n);
	#elif MODE==__reverse_
	std::sort(a,a+n,std::greater<data_type>() );
	#elif MODE==__sp_
	a[0]=a[n]=a[n>>1]=-(MAX_SCALE+1);
	#endif
	FILE *fin,*fout;
	fin=freopen("test.in","w",stdout);
	printf("%d\n",n);
	for (int i=0;i<n;++i) printf("%d ",a[i]);
	fclose(fin);

	fout=freopen("test.out","w",stdout);
	#if !(MODE==__sorted_)
	std::sort(a,a+n);
	#endif
	for (int i=0;i<n;++i) printf("%d ",a[i]);
	fclose(fout);
	
	return 0;
}

