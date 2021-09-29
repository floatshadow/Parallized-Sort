#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include"testrc.h"


data_type a[MAXN];
int n;
int  thread_cnt;


void merge_sort(data_type* begin ,data_type* end){ // [begin,end)
	  if (end-begin<=1) return;
		data_type* mid=begin+((end-begin)>>1);

		pthread_t left;
		left=0;
		if (thread_cnt < MAXTHREADS){
				__sync_fetch_and_add(&thread_cnt,1);
				Block left_part=(Block){merge_sort,begin,mid};	
				pthread_create(&left,NULL,__alloc_thread,(void*)&left_part);
		}else merge_sort(begin,mid);
		merge_sort(mid,end);
		
		if (left!=0) pthread_join(left,NULL);
		__merge(begin,end,mid);
}


int main(){
	thread_cnt=0;
	scanf("%d",&n);
	for (int i=0;i<n;++i) scanf(__READ_TYPE,a+i);
	#ifndef __CHECK
	double start,end;
	start=get_time();
	#endif
	merge_sort(a,a+n);
	#ifndef __CHECK
	end=get_time();
	FILE* fp=freopen("merge.txt","a+",stdout);
	printf("%.6lf\n",(end-start));
	fclose(fp);
	#endif
	#ifdef __CHECK
	for (int i=0;i<n;++i) printf(__PRINT_TYPE,a[i]);
	#endif
	
	return 0; 
}


