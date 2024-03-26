#ifndef CSP_PROC_RUNTIME_H
#define CSP_PROC_RUNTIME_H

#include <stdint.h>

#include <csp_proc/proc_types.h>
#include <csp_proc/proc_store.h>

#ifndef MAX_PROC_BLOCK_TIMEOUT
#define MAX_PROC_BLOCK_TIMEOUT (5700U)
#endif

#ifndef MIN_PROC_BLOCK_PERIOD_MS
#define MIN_PROC_BLOCK_PERIOD_MS (50U)
#endif

#ifndef MAX_PROC_RECURSION_DEPTH
#define MAX_PROC_RECURSION_DEPTH (1000U)
#endif

#ifndef MAX_PROC_CONCURRENT
#define MAX_PROC_CONCURRENT (16U)
#endif

/**
 * Initialize the procedure runtime and any necessary resources.
 * This function should only be called once. Any per-procedure configuration should be done in `proc_runtime_run`.
 *
 * @return 0 on success, -1 on failure
 */
int proc_runtime_init();

/**
 * Run a procedure stored in a given slot.
 *
 * @param proc_slot The slot of the procedure to run
 *
 * @return 0 on success, -1 on failure
 */
int proc_runtime_run(uint8_t proc_slot);

#endif  // CSP_PROC_RUNTIME_H
