/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "benchmark.h"
#include "processing.h"
#include "json.h"

#include <smmu.h>
#include <stdio.h>

static json_t *smmu_process(void *results)
{
    smmu_results_t *raw_results = results;

    result_desc_t desc = {
        .stable = false,
        .name = "Nothing overhead",
        .ignored = N_IGNORED
    };

    /* Execlude ccnt, user-level and loop overheads */
    desc.overhead = 0;

    result_t result = process_result(N_RUNS, raw_results->nothing_results, desc);

    result_set_t set = {
        .name = "nothing thread",
        .n_results = 1,
        .n_extra_cols = 0,
        .results = &result
    };

    json_t *array = json_array();
    json_array_append_new(array, result_set_to_json(set));

    return array;
}

static benchmark_t smmu_benchmark = {
    .name = "smmu",
    .enabled = config_set(CONFIG_APP_SMMUBENCH),
    .results_pages = BYTES_TO_SIZE_BITS_PAGES(sizeof(smmu_results_t), seL4_PageBits),
    .process = smmu_process,
    .init = blank_init
};

benchmark_t *smmu_benchmark_new(void)
{
    return &smmu_benchmark;
}



// /*
//  * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
//  *
//  * SPDX-License-Identifier: BSD-2-Clause
//  */
// #include <autoconf.h>
// #include <jansson.h>
// #include <sel4bench/sel4bench.h>
// #include <utils/util.h>
// #include <smmu.h>
// #include <stdio.h>

// #include "benchmark.h"
// #include "json.h"
// #include "math.h"
// #include "printing.h"
// #include "processing.h"

// static json_t *smmu_results(void *r)
// {
//     smmu_results_t *raw_results = r;

//     result_desc_t desc = {
//         .stable = false,
//         .name = "Random results",
//         .ignored = N_IGNORED,
//         .overhead = 0
//     };

//     result_t result = process_result(N_RUNS, raw_results->random_results, desc);

//     result_set_t set = {
//         .name = "Random",
//         .n_results = 1,
//         .n_extra_cols = 0,
//         .results = &result
//     };

//     json_t *array = json_array();
//     json_array_append_new(array, result_set_to_json(set));
//     return array;
// }

// static benchmark_t smmu_benchmark = {
//     .name = "smmu",
//     .enabled = config_set(CONFIG_APP_SMMUBENCH),
//     .results_pages = BYTES_TO_SIZE_BITS_PAGES(sizeof(smmu_results_t),
//                                               seL4_PageBits),
//     .process = smmu_results,
//     .init = blank_init
// };

// benchmark_t *smmu_benchmark_new(void)
// {
//     return &smmu_benchmark;
// }
