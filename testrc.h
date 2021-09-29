#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<ctype.h>
#include<sys/time.h>
#ifndef __TESTRC_H_
#define __TESTRC_H_


#ifndef MAXN
#define MAXN 20000000
#endif
//-------------default 4 threads
#ifndef MAXTHREADS
#define MAXTHREADS 4
#endif

#ifndef TYPE
#define TYPE int
//--------------testing other types :default int
typedef int data_type;
#define __TYPE "%d"
#endif



//-------------read and print for diffirent types of data

#if TYPE==INT
typedef int data_type;
#define __READ_TYPE "%d"
#define __PRINT_TYPE "%d "
#elif TYPE==DOUBLE
typedef double data_type;
#define __READ_TYPE "%lf"
#define __PRINT_TYPE "%lf "
#endif


//-------------strcut for arg int thread func
typedef struct __block{
		void (*__sort_func)(data_type*,data_type*);  //[begin,end)
		data_type *begin,*end;
} Block;

extern data_type __medain(const data_type,const data_type,const data_type);
extern void __merge(data_type *begin,data_type* end,data_type *mid);
extern data_type* __partition(data_type* begin,data_type* end,data_type pivot);
extern void* __alloc_thread(void*);
extern double get_time();
extern void swap(data_type *a,data_type *b);

//-------------mode of generators
#define __default_ 		0
#define __sorted_			1
#define __reverse_ 		2
#define __repaeated_ 	3
#define __sp_ 				4
#define __medain_			5



#endif
