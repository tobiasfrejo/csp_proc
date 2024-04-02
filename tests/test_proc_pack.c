#include <stdio.h>

#include <criterion/criterion.h>
#include <criterion/theories.h>

#include <csp/csp_types.h>
#include <csp_proc/proc_types.h>
#include <csp_proc/proc_pack.h>

TheoryDataPoints(proc_pack_unpack, test_pack_unpack_instruction_types) = {
	DataPoints(proc_instruction_type_t, PROC_BLOCK, PROC_IFELSE, PROC_SET, PROC_UNOP, PROC_BINOP, PROC_CALL, PROC_NOOP),
};

Theory((proc_instruction_type_t type), proc_pack_unpack, test_pack_unpack_instruction_types) {
	proc_t original_proc;
	csp_packet_t packet;

	original_proc.instruction_count = 1;
	original_proc.instructions[0].node = 1;
	original_proc.instructions[0].type = type;

	switch (type) {
		case PROC_BLOCK:
			original_proc.instructions[0].instruction.block.param_a = "param_a";
			original_proc.instructions[0].instruction.block.op = OP_EQ;
			original_proc.instructions[0].instruction.block.param_b = "param_b";
			break;
		case PROC_IFELSE:
			original_proc.instructions[0].instruction.ifelse.param_a = "param_a";
			original_proc.instructions[0].instruction.ifelse.op = OP_NEQ;
			original_proc.instructions[0].instruction.ifelse.param_b = "param_b";
			break;
		case PROC_SET:
			original_proc.instructions[0].instruction.set.param = "param";
			original_proc.instructions[0].instruction.set.value = "value";
			break;
		case PROC_UNOP:
			original_proc.instructions[0].instruction.unop.param = "param";
			original_proc.instructions[0].instruction.unop.op = OP_INC;
			original_proc.instructions[0].instruction.unop.result = "result";
			break;
		case PROC_BINOP:
			original_proc.instructions[0].instruction.binop.param_a = "param_a";
			original_proc.instructions[0].instruction.binop.op = OP_ADD;
			original_proc.instructions[0].instruction.binop.param_b = "param_b";
			original_proc.instructions[0].instruction.binop.result = "result";
			break;
		case PROC_CALL:
			original_proc.instructions[0].instruction.call.procedure_slot = 1;
			break;
		case PROC_NOOP:
			break;
	}

	// Pack the proc
	int pack_result = pack_proc_into_csp_packet(&original_proc, &packet);
	cr_assert(pack_result == 0, "Packing failed");

	// Unpack the proc
	proc_t new_proc;
	int unpack_result = unpack_proc_from_csp_packet(&new_proc, &packet);
	cr_assert(unpack_result == 0, "Unpacking failed");

	cr_assert(original_proc.instruction_count == new_proc.instruction_count, "Instruction counts do not match");
	cr_assert(original_proc.instructions[0].node == new_proc.instructions[0].node, "Nodes do not match");
	cr_assert(original_proc.instructions[0].type == new_proc.instructions[0].type, "Types do not match");

	switch (type) {
		case PROC_BLOCK:
			cr_assert(strcmp(original_proc.instructions[0].instruction.block.param_a, new_proc.instructions[0].instruction.block.param_a) == 0, "param_a does not match");
			cr_assert(original_proc.instructions[0].instruction.block.op == new_proc.instructions[0].instruction.block.op, "op does not match");
			cr_assert(strcmp(original_proc.instructions[0].instruction.block.param_b, new_proc.instructions[0].instruction.block.param_b) == 0, "param_b does not match");
			break;
		case PROC_IFELSE:
			cr_assert(strcmp(original_proc.instructions[0].instruction.ifelse.param_a, new_proc.instructions[0].instruction.ifelse.param_a) == 0, "param_a does not match");
			cr_assert(original_proc.instructions[0].instruction.ifelse.op == new_proc.instructions[0].instruction.ifelse.op, "op does not match");
			cr_assert(strcmp(original_proc.instructions[0].instruction.ifelse.param_b, new_proc.instructions[0].instruction.ifelse.param_b) == 0, "param_b does not match");
			break;
		case PROC_SET:
			cr_assert(strcmp(original_proc.instructions[0].instruction.set.param, new_proc.instructions[0].instruction.set.param) == 0, "param does not match");
			cr_assert(strcmp(original_proc.instructions[0].instruction.set.value, new_proc.instructions[0].instruction.set.value) == 0, "value does not match");
			break;
		case PROC_UNOP:
			cr_assert(strcmp(original_proc.instructions[0].instruction.unop.param, new_proc.instructions[0].instruction.unop.param) == 0, "param does not match");
			cr_assert(original_proc.instructions[0].instruction.unop.op == new_proc.instructions[0].instruction.unop.op, "op does not match");
			cr_assert(strcmp(original_proc.instructions[0].instruction.unop.result, new_proc.instructions[0].instruction.unop.result) == 0, "result does not match");
			break;
		case PROC_BINOP:
			cr_assert(strcmp(original_proc.instructions[0].instruction.binop.param_a, new_proc.instructions[0].instruction.binop.param_a) == 0, "param_a does not match");
			cr_assert(original_proc.instructions[0].instruction.binop.op == new_proc.instructions[0].instruction.binop.op, "op does not match");
			cr_assert(strcmp(original_proc.instructions[0].instruction.binop.param_b, new_proc.instructions[0].instruction.binop.param_b) == 0, "param_b does not match");
			cr_assert(strcmp(original_proc.instructions[0].instruction.binop.result, new_proc.instructions[0].instruction.binop.result) == 0, "result does not match");
			break;
		case PROC_CALL:
			cr_assert(original_proc.instructions[0].instruction.call.procedure_slot == new_proc.instructions[0].instruction.call.procedure_slot, "procedure_slot does not match");
			break;
		case PROC_NOOP:
			break;
	}
}

Test(proc_pack_unpack, test_pack_unpack_variety) {
	proc_t original_proc;
	csp_packet_t packet;

	original_proc.instruction_count = 7;
	original_proc.instructions[0].node = 1;
	original_proc.instructions[0].type = PROC_BLOCK;
	original_proc.instructions[0].instruction.block.param_a = "param_a";
	original_proc.instructions[0].instruction.block.op = OP_LE;
	original_proc.instructions[0].instruction.block.param_b = "param_b";

	original_proc.instructions[1].node = 253;
	original_proc.instructions[1].type = PROC_SET;
	original_proc.instructions[1].instruction.set.param = "param_";
	original_proc.instructions[1].instruction.set.value = "1337.42";

	original_proc.instructions[2].node = 395;
	original_proc.instructions[2].type = PROC_UNOP;
	original_proc.instructions[2].instruction.unop.param = "pa_ram";
	original_proc.instructions[2].instruction.unop.op = OP_IDT;
	original_proc.instructions[2].instruction.unop.result = "result";

	original_proc.instructions[3].node = 4;
	original_proc.instructions[3].type = PROC_BINOP;
	original_proc.instructions[3].instruction.binop.param_a = "param[63]";
	original_proc.instructions[3].instruction.binop.op = OP_LSH;
	original_proc.instructions[3].instruction.binop.param_b = "param[5]";
	original_proc.instructions[3].instruction.binop.result = "result[0]";

	original_proc.instructions[4].node = 79;
	original_proc.instructions[4].type = PROC_NOOP;

	original_proc.instructions[5].node = 65;
	original_proc.instructions[5].type = PROC_IFELSE;
	original_proc.instructions[5].instruction.ifelse.param_a = "param_a";
	original_proc.instructions[5].instruction.ifelse.op = OP_GT;
	original_proc.instructions[5].instruction.ifelse.param_b = "param_b";

	original_proc.instructions[6].node = 1525;
	original_proc.instructions[6].type = PROC_CALL;
	original_proc.instructions[6].instruction.call.procedure_slot = 42;

	// Pack the proc
	int pack_result = pack_proc_into_csp_packet(&original_proc, &packet);
	cr_assert(pack_result == 0, "Packing failed");

	// Unpack the proc
	proc_t new_proc;
	int unpack_result = unpack_proc_from_csp_packet(&new_proc, &packet);
	cr_assert(unpack_result == 0, "Unpacking failed");

	cr_assert(original_proc.instruction_count == new_proc.instruction_count, "Instruction counts do not match");
	for (int i = 0; i < original_proc.instruction_count; i++) {
		cr_assert(original_proc.instructions[i].node == new_proc.instructions[i].node, "Nodes do not match");
		cr_assert(original_proc.instructions[i].type == new_proc.instructions[i].type, "Types do not match");

		switch (original_proc.instructions[i].type) {
			case PROC_BLOCK:
				cr_assert_str_eq(original_proc.instructions[i].instruction.block.param_a, new_proc.instructions[i].instruction.block.param_a, "Block param_a does not match");
				cr_assert(original_proc.instructions[i].instruction.block.op == new_proc.instructions[i].instruction.block.op, "Block op does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.block.param_b, new_proc.instructions[i].instruction.block.param_b, "Block param_b does not match");
				break;
			case PROC_SET:
				cr_assert_str_eq(original_proc.instructions[i].instruction.set.param, new_proc.instructions[i].instruction.set.param, "Set param does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.set.value, new_proc.instructions[i].instruction.set.value, "Set value does not match");
				break;
			case PROC_UNOP:
				cr_assert_str_eq(original_proc.instructions[i].instruction.unop.param, new_proc.instructions[i].instruction.unop.param, "Unop param does not match");
				cr_assert(original_proc.instructions[i].instruction.unop.op == new_proc.instructions[i].instruction.unop.op, "Unop op does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.unop.result, new_proc.instructions[i].instruction.unop.result, "Unop result does not match");
				break;
			case PROC_BINOP:
				cr_assert_str_eq(original_proc.instructions[i].instruction.binop.param_a, new_proc.instructions[i].instruction.binop.param_a, "Binop param_a does not match");
				cr_assert(original_proc.instructions[i].instruction.binop.op == new_proc.instructions[i].instruction.binop.op, "Binop op does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.binop.param_b, new_proc.instructions[i].instruction.binop.param_b, "Binop param_b does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.binop.result, new_proc.instructions[i].instruction.binop.result, "Binop result does not match");
				break;
			case PROC_CALL:
				cr_assert(original_proc.instructions[i].instruction.call.procedure_slot == new_proc.instructions[i].instruction.call.procedure_slot, "Call procedure_slot does not match");
				break;
			case PROC_IFELSE:
				cr_assert_str_eq(original_proc.instructions[i].instruction.ifelse.param_a, new_proc.instructions[i].instruction.ifelse.param_a, "Ifelse param_a does not match");
				cr_assert(original_proc.instructions[i].instruction.ifelse.op == new_proc.instructions[i].instruction.ifelse.op, "Ifelse op does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.ifelse.param_b, new_proc.instructions[i].instruction.ifelse.param_b, "Ifelse param_b does not match");
				break;
			case PROC_NOOP:
				break;
			default:
				cr_assert(false, "Unknown instruction type");
				break;
		}
	}
}

Test(proc_pack_unpack, test_pack_does_not_mutate) {
	proc_t original_proc, copy_proc;
	csp_packet_t packet;

	original_proc.instruction_count = 2;

	original_proc.instructions[0].node = 1;
	original_proc.instructions[0].type = PROC_BLOCK;
	original_proc.instructions[0].instruction.block.param_a = "param_a";
	original_proc.instructions[0].instruction.block.op = OP_LE;
	original_proc.instructions[0].instruction.block.param_b = "param_b";

	original_proc.instructions[1].node = 4;
	original_proc.instructions[1].type = PROC_BINOP;
	original_proc.instructions[1].instruction.binop.param_a = "param[63]";
	original_proc.instructions[1].instruction.binop.op = OP_LSH;
	original_proc.instructions[1].instruction.binop.param_b = "param[5]";
	original_proc.instructions[1].instruction.binop.result = "result[0]";

	// Create a copy of original_proc for later comparison
	copy_proc = original_proc;

	// Pack the proc
	int pack_result = pack_proc_into_csp_packet(&original_proc, &packet);
	cr_assert(pack_result == 0, "Packing failed");

	// Check that original_proc has not been mutated
	cr_assert(original_proc.instruction_count == copy_proc.instruction_count, "Instruction counts do not match");
	for (int i = 0; i < original_proc.instruction_count; i++) {
		cr_assert(original_proc.instructions[i].node == copy_proc.instructions[i].node, "Nodes do not match");
		cr_assert(original_proc.instructions[i].type == copy_proc.instructions[i].type, "Types do not match");

		switch (original_proc.instructions[i].type) {
			case PROC_BLOCK:
				cr_assert_str_eq(original_proc.instructions[i].instruction.block.param_a, copy_proc.instructions[i].instruction.block.param_a, "Block param_a does not match");
				cr_assert(original_proc.instructions[i].instruction.block.op == copy_proc.instructions[i].instruction.block.op, "Block op does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.block.param_b, copy_proc.instructions[i].instruction.block.param_b, "Block param_b does not match");
				break;
			case PROC_BINOP:
				cr_assert_str_eq(original_proc.instructions[i].instruction.binop.param_a, copy_proc.instructions[i].instruction.binop.param_a, "Binop param_a does not match");
				cr_assert(original_proc.instructions[i].instruction.binop.op == copy_proc.instructions[i].instruction.binop.op, "Binop op does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.binop.param_b, copy_proc.instructions[i].instruction.binop.param_b, "Binop param_b does not match");
				cr_assert_str_eq(original_proc.instructions[i].instruction.binop.result, copy_proc.instructions[i].instruction.binop.result, "Binop result does not match");
				break;
			default:
				cr_assert(false, "Unknown instruction type");
				break;
		}
	}
}
