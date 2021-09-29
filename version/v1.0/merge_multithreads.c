#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include"testrc.h"


data_type a[MAXN];
pthread_t thread[MAXTHREADS];
int thread_cnt;
int n;
//-------------declaration of functions

void __merge(int begin,int end,int mid);
void merge_sort(int begin ,int end); // [begin,end)
void* alloc_thread_merge_sort(void* block);
//------------end declaration

double get_time(){
	struct timeval t;
	gettimeofday(&t,NULL);
	return t.tv_sec + t.tv_usec/1000000.0;
}


void __merge(int begin,int end,int mid){
		data_type* tmp=(data_type*)malloc(sizeof(data_type)*(end-begin));
		data_type* p=tmp;
		int i,j;
		i=begin; j=mid;
		while (i<mid &&  j<end) {
			if (a[i]<a[j]) *(p++)=a[i++];
			else *(p++)=a[j++]; 
		}
		while (i<mid) *(p++)=a[i++];
		while (j<end) *(p++)=a[j++];
		memcpy(a+begin,tmp,sizeof(data_type)*(end-begin));
		free(tmp);
}

void* alloc_thread_merge_sort(void* block){
		merge_sort( ((Block*)block)->begin,((Block*)block)->end);
	  return NULL;		
}


void merge_sort(int begin ,int end){ // [begin,end)
	  if (end-begin==1) return;
		int mid=(begin+end)>>1;
		pthread_t* ptr=NULL;
		if (thread_cnt < MAXTHREADS){
				ptr = &thread[thread_cnt++];
				Block left_part=(Block){begin,mid};	
				pthread_create(ptr,NULL,alloc_thread_merge_sort,(void*)&left_part);
		}else merge_sort(begin,mid,dep+1);
		merge_sort(mid,end);
		if (ptr!=NULL) pthread_join(*ptr,NULL);
		__merge(begin,end,mid);
}


int main(){
	scanf("%d",&n);
	for (int i=0;i<n;++i) scanf(__READ_TYPE,a+i);
	#ifndef __CHECK
	double start,end;
	start=get_time();
	thread_cnt=0;
	#endif
	merge_sort(0,n);
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


