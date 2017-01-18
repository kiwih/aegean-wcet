#include <stdio.h>
#include <machine/patmos.h>
#include <machine/rtc.h>

void __attribute__ ((noinline)) timed_task() {
	volatile int x;
	volatile int y;
	_Pragma("loopbound min 0 max 99")
	for(x = 0; x < 100; x++) {
		y = x;
	}
}

int main(int argc, char **argv) {
	unsigned long long start_time;
	unsigned long long end_time;

	start_time = get_cpu_cycles();

	timed_task();

	end_time = get_cpu_cycles();
	printf("Time taken: %lld cycles\n", end_time-start_time-3);
}