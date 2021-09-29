#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"testrc.h"

data_type a[MAXN];
int n,thread_cnt;


void quick_sort(data_type* first,data_type* last){  		
	data_type* cut=__partition(first,last,*(first+((last-first)>>1)));

	pthread_t left;
	left=0;
	if (cut-first > 1){
			if (thread_cnt < MAXTHREADS){
			__sync_fetch_and_add(&thread_cnt,1);
			Block left_part=(Block){quick_sort,first,cut};	
			pthread_create(&left,NULL,__alloc_thread,(void*)&left_part);
		}else quick_sort(first,cut);
	}
  if (last - cut > 1)quick_sort(cut,last);
	if (left!=0) pthread_join(left,NULL);
}



int main(){
		scanf("%d",&n);
		for (int i=0;i<n;++i) scanf(__READ_TYPE,a+i);
		thread_cnt=0;
		#ifndef __CHECK
		double start,end;
		start=get_time();
		#endif
		quick_sort(a,a+n);
		#ifndef __CHECK
		end=get_time();
		FILE* fp=freopen("qsort.txt","a+",stdout);
		printf(" %.6lf\n",end-start);
		fclose(fp);
		#endif
		#ifdef __CHECK
		for (int i=0;i<n;i++) printf(__PRINT_TYPE,a[i]);
		#endif
		return 0;
}
