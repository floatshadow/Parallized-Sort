#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"testrc.h"

pthread_t thread[MAXTHREADS];
data_type a[MAXN];
int n,thread_cnt;

void swap(data_type *a,data_type *b);
void quick_sort(int ,int);
void* __quick_sort_alloc_thread(void*);


double get_time(){
	struct timeval t;
	gettimeofday(&t,NULL);
	return t.tv_sec + t.tv_usec/1000000.0;

}
void swap(data_type *a,data_type *b){
	data_type temp=*a;
	*a=*b;
	*b=temp;
}

void* __quick_sort_alloc_thread(void* arg){
	Block* block=(Block*)arg;
	quick_sort(block->begin,block->end);
	return NULL;	
}

void quick_sort(int l,int r){  //sort[l,r]		
	data_type mid=a[(l+r)>>1];
	int i,j;
	i=l; j=r;
	do{
		while (a[i]<mid) i++;
		while (a[j]>mid) j--;
		if  (i<=j){
			swap(a+i,a+j);
			i++; j--;
		}
	}while (i<=j);
	pthread_t* ptr=NULL;
	if (l<j){
		if (thread_cnt < MAXTHREADS){
			ptr=&thread[thread_cnt++];
			Block block=(Block){l,j};
			pthread_create(ptr,NULL,__quick_sort_alloc_thread,(void*)&block);
		} else quick_sort(l,j);
	}
	if (i<r) quick_sort(i,r);
	if (ptr!=NULL) pthread_join(*ptr,NULL);
}


int main(){
		scanf("%d",&n);
		for (int i=0;i<n;++i) scanf(__READ_TYPE,a+i);
		thread_cnt=0;
		#ifndef __CHECK
		double start,end;
		start=get_time();
		#endif
		quick_sort(0,n-1);
		#ifndef __CHECK
		end=get_time();
		FILE* fp=freopen("qsort.txt","a+",stdout);
		printf("%.6lf\n",end-start);
		fclose(fp);
		#endif
		#ifdef __CHECK
		for (int i=0;i<n;i++) printf(__PRINT_TYPE,a[i]);
		#endif
		return 0;
}
