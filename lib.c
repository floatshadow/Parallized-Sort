#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>
#include<pthread.h>
#include"testrc.h"


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

data_type __medain(const data_type a,const data_type b,const data_type c){
	if  (a<b)
		if (b<c)
			return b;
		else if (a<c)
			return c;
		else 
			return a;
	else if (a<c)
		return a;
	else if (b<c)
		return c;
	else 
		return b;
}

data_type* __partition(data_type *first,data_type *last,data_type pivot){
	for (;;){
		while (*first < pivot) ++first;
		--last;
		while (pivot < *last) --last;
		if (!(first < last)) return first;
		swap(first,last);
		++first;
	}
}

void __merge(data_type* begin,data_type* end,data_type* mid){
		data_type* tmp=(data_type*)malloc(sizeof(data_type)*(end-begin));
		data_type *p,*i,*j;
		p=tmp; i=begin; j=mid;
		while (i<mid &&  j<end) {
			if (*i<*j) *(p++)=*(i++);
			else *(p++)=*(j++); 
		}
		memcpy(p,i,sizeof(data_type)*(mid-i));
		memcpy(p,j,sizeof(data_type)*(end-j));
		memcpy(begin,tmp,sizeof(data_type)*(end-begin));
		free(tmp);
}

void* __alloc_thread(void* block){
		Block *arg=(Block*)block;
		(arg->__sort_func)(arg->begin,arg->end);
}
