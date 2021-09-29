#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>
#include"testrc.h"

data_type a[MAXN];
int n;


void quick_sort(data_type* first,data_type* last){  // [l,r]
	data_type* cut=__partition(first,last,*(first+(rand()%(last-first))));
	if (cut-first > 1) quick_sort(first,cut);
	if (last-cut > 1) quick_sort(cut,last);
}

int main(){
		srand(time(0));
		scanf("%d",&n);
		for (int i=0;i<n;++i) scanf(__READ_TYPE,a+i);
		#ifndef __CHECK
		double start,end;
		start=get_time();
		#endif
		quick_sort(a,a+n);
		#ifndef __CHECK
		end=get_time();
		FILE* fp=freopen("qsort_rand.txt","a+",stdout);
		printf("%d %.6lf ",n,end-start);
		fclose(fp);
		#endif
		#ifdef __CHECK
		for (int i=0;i<n;++i) printf(__PRINT_TYPE,a[i]);
		#endif
		return 0;
}

