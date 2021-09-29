#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"testrc.h"
#include<sys/time.h>
data_type a[MAXN];
int n;

double get_time(){
	struct timeval t;
	gettimeofday(&t,NULL);
	return t.tv_sec + t.tv_usec/1000000.0;
}


// array a, [begin,end)
void merge_sort(data_type *a,int begin,int end){
	if (end-begin==1) return;
	int mid=(begin+end)>>1;
	merge_sort(a,begin,mid);
	merge_sort(a,mid,end);
	data_type *tmp=(data_type*)malloc(sizeof(data_type)*(end-begin));
	data_type *p=tmp;
	int  i=begin,j=mid;
	while (i<mid && j<end){
		if (a[i]<a[j]) *(p++)=a[i++];
			else *(p++)=a[j++];
	}
	while (i<mid) *(p++)=a[i++];
	while (j<end) *(p++)=a[j++];
	memcpy(a+begin,tmp,sizeof(data_type)*(end-begin));
	free(tmp);
} 


int main(){
	scanf("%d",&n);
	for (int i=0;i<n;++i) scanf(__READ_TYPE,a+i);
	#ifndef __CHECK
	double start,end;
	start=get_time();
	#endif
	merge_sort(a,0,n);
	#ifndef __CHECK
	end=get_time();
  FILE* fp=freopen("merge.txt","a+",stdout);
	printf("%d %.6lf ",n,(end-start));
	fclose(fp);
	#endif
	#ifdef __CHECK
	for (int i=0;i<n;++i) printf(__PRINT_TYPE,a[i]);
	#endif
	return 0;
}
