#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"testrc.h"
#include<omp.h>
#include<sys/time.h>
data_type a[MAXN];
int n;


// array a, [begin,end)
void merge_sort(data_type* begin,data_type* end){
	int size=end-begin;
	data_type* i;
	for (int gap=1;gap<size;gap<<=1){
			for (i=begin;i+(gap<<1)<=end;i+=(gap<<1)) __merge(i,i+(gap<<1),i+gap);
			if (i<end-gap) __merge(i,end,i+gap);
	}
} 


int main(){
	scanf("%d",&n);
	for (int i=0;i<n;++i) scanf(__READ_TYPE,a+i);
	#ifndef __CHECK
	double start,end;
	start=get_time();
	#endif
	merge_sort(a,a+n);
	#ifndef __CHECK
	end=get_time();
  FILE* fp=freopen("merge_bottom_up.txt","a+",stdout);
	printf("%d %.6lf ",n,(end-start));
	fclose(fp);
	#endif
	#ifdef __CHECK
	for (int i=0;i<n;++i) printf(__PRINT_TYPE,a[i]);
	#endif
	return 0;
}
