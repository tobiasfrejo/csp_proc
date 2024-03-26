// FreeRTOS implementation of csp_proc runtime

#include <csp_proc/proc_runtime.h>

/**
 * Run a procedure stored in a given slot.
 *
 * @param proc_slot The slot of the procedure to run
 *
 * @return 0 on success, -1 on failure
 */
int proc_runtime_run(uint8_t proc_slot) {
	proc_t * proc = get_proc(proc_slot);
	if (proc == NULL) {
		printf("Procedure not found\n");
		return -1;
	}

	// for (int i = 0; i < proc->instruction_count; i++) {
	//     proc_instruction_t instruction = proc->instructions[i];
	//     switch (instruction.type) {
	//         case PROC_BLOCK:
	//             proc_runtime_block(instruction.instruction);
	//             break;
	//         case PROC_IFELSE:
	//             proc_runtime_ifelse(instruction.instruction);
	//             break;
	//         case PROC_SET:
	//             proc_runtime_set(instruction.instruction);
	//             break;
	//         case PROC_UNOP:
	//             proc_runtime_unop(instruction.instruction);
	//             break;
	//         case PROC_BINOP:
	//             proc_runtime_binop(instruction.instruction);
	//             break;
	//         case PROC_CALL:
	//             proc_runtime_call(instruction.instruction);
	//             break;
	//         default:
	//             printf("Unknown instruction type\n");
	//             break;
	//     }
	// }

	return 0;
}
