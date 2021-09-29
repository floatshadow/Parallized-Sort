#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"testrc.h"
#include<sys/time.h>
data_type a[MAXN];
int n;



// array a, [begin,end)
void merge_sort(data_type* begin,data_type* end){
	if (end-begin==1) return;
	data_type* mid=begin+((end-begin)>>1);
	merge_sort(begin,mid);
	merge_sort(mid,end);
	__merge(begin,end,mid);
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
  FILE* fp=freopen("merge.txt","a+",stdout);
	printf("%d %.6lf ",n,(end-start));
	fclose(fp);
	#endif
	#ifdef __CHECK
	for (int i=0;i<n;++i) printf(__PRINT_TYPE,a[i]);
	#endif
	return 0;
}
