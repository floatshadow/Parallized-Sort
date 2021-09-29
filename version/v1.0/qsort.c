#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>
#include"testrc.h"

data_type a[MAXN];
int n;

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

void quick_sort(int l,int r){  // [l,r]
	data_type mid=a[(l+r)>>1];
	int i=l,j=r;
	do{
		while (a[i]<mid) i++;
		while (a[j]>mid) j--;
		if (i<=j){
			swap(a+i,a+j);
			i++; j--;
		}
	}while (i<=j);
	if (l<j) quick_sort(l,j);
	if (i<r) quick_sort(i,r);
}

int main(){
		scanf("%d",&n);
		for (int i=0;i<n;++i) scanf(__READ_TYPE,a+i);
		#ifndef __CHECK
		double start,end;
		start=get_time();
		#endif
		quick_sort(0,n-1);
		#ifndef __CHECK
		end=get_time();
		FILE* fp=freopen("qsort.txt","a+",stdout);
		printf("%d %.6lf ",n,end-start);
		fclose(fp);
		#endif
		#ifdef __CHECK
		for (int i=0;i<n;++i) printf(__PRINT_TYPE,a[i]);
		#endif
		return 0;
}

