#include <criterion/criterion.h>

#include <csp/csp_types.h>
#include <csp_proc/proc_types.h>
#include <csp_proc/proc_pack.h>

Test(proc_pack_unpack, test_pack_unpack) {
	proc_t original_proc;
	csp_packet_t packet;

	original_proc.instruction_count = 1;
	original_proc.instructions[0].node = 1;
	original_proc.instructions[0].type = PROC_BLOCK;
	original_proc.instructions[0].instruction.block.param_a = "param_a";
	original_proc.instructions[0].instruction.block.op = OP_EQ;
	original_proc.instructions[0].instruction.block.param_b = "param_b";

	int pack_result = pack_proc_into_csp_packet(&original_proc, &packet);
	cr_assert(pack_result == 0, "Packing failed");

	proc_t new_proc;
	int unpack_result = unpack_proc_from_csp_packet(&new_proc, &packet);
	cr_assert(unpack_result == 0, "Unpacking failed");

	cr_assert(original_proc.instruction_count == new_proc.instruction_count, "Instruction counts do not match");
	cr_assert(original_proc.instructions[0].node == new_proc.instructions[0].node, "Nodes do not match");
	cr_assert(original_proc.instructions[0].type == new_proc.instructions[0].type, "Types do not match");
	cr_assert(strcmp(original_proc.instructions[0].instruction.block.param_a, new_proc.instructions[0].instruction.block.param_a) == 0, "param_a does not match");
	cr_assert(original_proc.instructions[0].instruction.block.op == new_proc.instructions[0].instruction.block.op, "op does not match");
	cr_assert(strcmp(original_proc.instructions[0].instruction.block.param_b, new_proc.instructions[0].instruction.block.param_b) == 0, "param_b does not match");
}
