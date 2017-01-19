# aegean wcet example

The purpose of this repository is to show how to both *measure* and *compute* the WCET for the simple function below on the t-crest platform.

```c
void __attribute__ ((noinline)) timed_task() {
	volatile int x;
	volatile int y;
	_Pragma("loopbound min 0 max 99")
	for(x = 0; x < 100; x++) {
		y = x;
	}
}
```

You should have t-crest, platin etc installed normally.

`make build` will make the executable and put it into the t-crest patmos tmp folder for download to the FPGA (using `make download APP=easy-wcet` from within $TCREST/patmos/)

`make wcet` will make the WCET report.

In the Makefile you can change / alter the parameters for the timing analysis (pml-config command). See the wcet-config section.

Results (all for DE2-115):

| Device        | WCET of timed_task (cycles) |
| ------------- | ---------------------------:|
| Aegean 4-core | 17445                       |
| Patmos 1-core | 5483                        |
| Platin wcet   | 52988                       |

Note: Platin WCET is run with pml-config --tdelay=83 --bsize=16 as each core has its own slot in the arbiter and 4 cores have 4 slots of each 21 cycles, making --tdelay = 4 x 21-1 = 83.
Note: MS have updated to use --gtime 83 and --tdelay 0, which results in less cycles.

--disable-ait is also set as Ait was not available for this analysis.

