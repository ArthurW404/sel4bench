/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <autoconf.h>
#include <sel4benchsmmu/gen_config.h>
#include <stdio.h>

#include <sel4/sel4.h>
#include <sel4bench/arch/sel4bench.h>
#include <sel4runtime.h>
#include <muslcsys/vsyscall.h>
#include <utils/attribute.h>

#include <benchmark.h>
#include <smmu.h>

#define NOPS ""

// #include <arch/hardware.h>

void abort(void)
{
    benchmark_finished(EXIT_FAILURE);
}

void measure_nothing(ccnt_t *results)
{
    ccnt_t start, end;
    for (int i = 0; i < N_RUNS; i++) {
        SEL4BENCH_READ_CCNT(start);
        // DO_REAL_NULLSYSCALL();
        SEL4BENCH_READ_CCNT(end);
        results[i] = (end - start);
    }

}

static env_t *env;

void CONSTRUCTOR(MUSLCSYS_WITH_VSYSCALL_PRIORITY) init_env(void)
{
    static size_t object_freq[seL4_ObjectTypeCount] = {0};

    env = benchmark_get_env(
              sel4runtime_argc(),
              sel4runtime_argv(),
              sizeof(smmu_results_t),
              object_freq
          );
}

int main(int argc, char **argv)
{
    printf("==> In smmu bench main???\n");
    UNUSED int error;
    smmu_results_t *results;

    results = (smmu_results_t *) env->results;

    sel4bench_init();

    /* measure overhead */
    measure_nothing(results->nothing_results);

    /* done -> results are stored in shared memory so we can now return */
    benchmark_finished(EXIT_SUCCESS);
    return 0;
}


// /*
//  * Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
//  *
//  * SPDX-License-Identifier: BSD-2-Clause
//  */
// #include <autoconf.h>
// // #include <sel4benchpagemapping/gen_config.h>
// #include <sel4benchsmmu/gen_config.h>
// #include <vka/capops.h>
// #include <sel4bench/arch/sel4bench.h>
// #include <benchmark.h>
// #include <smmu.h>
// #include <sel4runtime.h>
// #include <muslcsys/vsyscall.h>
// #include <utils/attribute.h>
// #include <stdio.h>

// static env_t *env;


// void measure_random(ccnt_t *results)
// {
//     ccnt_t start, end;
//     for (int i = 0; i < N_RUNS; i++) {
//         results[i] = 0;
//     }
// }

// int main(int argc, char *argv[])
// {   
//     printf("==> In smmu bench main???\n");

//     UNUSED int error;
//     smmu_results_t *results;

//     results = (smmu_results_t *) env->results;


//     sel4bench_init();

//     // measure_overhead(results);
//     // run_fault_benchmark(env, results);

//     measure_random(results->random_results);

//     /* done -> results are stored in shared memory so we can now return */
//     benchmark_finished(EXIT_SUCCESS);
//     return 0;
// }
