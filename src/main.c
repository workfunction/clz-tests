#include <stdio.h>
#ifdef CHK
#include <omp.h>
#endif
#include <time.h>
#include "main.h"

#define MAX_NUM 0x000FFFFF

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int check(uint32_t x, int n) {
	return ((!x) && n >> 5) || (!(x >> (31 - n) >> 1) && (x >> (31 - n)));
}

int main(){
	uint32_t i = 0;

#ifdef CHK
	#pragma omp parallel default (shared) private(i) num_threads(omp_get_max_threads())
	#pragma omp for schedule(static)
	for (i = 0 ; i <= 0xFFFFFFFE; i++) {
		!(check(i, clz(i))) && printf ( LIGHT_RED "Error in %u count %d\n" NONE, i, clz(i));
		if((i & (i - 1)) == 0)
			printf( DARY_GRAY "Check point %u\n" NONE, i);
	}

	printf ( LIGHT_GREEN "Check done!\n" NONE );
#else
	struct timespec start, end;
	double cpu_time;
	char foutput[] = "output/output_" FUNC ".txt";
	FILE* out = fopen(foutput, "w");
	for (i = 0 ; i <= MAX_NUM; i++) {
		clock_gettime(CLOCK_REALTIME, &start);
		clz(i);
		clock_gettime(CLOCK_REALTIME, &end);
		cpu_time = diff_in_second(start, end);
		fprintf(out, "%u %lf\n",i,cpu_time*1000000);

		if((i & (i - 1)) == 0)
			printf( DARY_GRAY "Check point %u\n" NONE, i);
	}
#endif	
}

