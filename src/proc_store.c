#include <csp_proc/proc_store.h>

proc_t proc_store[MAX_PROC_SLOT + 1] = {0};

int delete_proc(uint8_t slot) {
	if (slot < 0 || slot > MAX_PROC_SLOT) {
		return -1;
	}
	for (int i = 0; i < proc_store[slot].instruction_count; i++) {
		proc_free_instruction(&proc_store[slot].instructions[i]);
	}
	proc_store[slot].instruction_count = 0;
	return 0;
}

void reset_proc_store() {
	for (int i = 0; i < MAX_PROC_SLOT + 1; i++) {
		delete_proc(i);
	}
}

int set_proc(proc_t * proc, uint8_t slot, int overwrite) {
	if (proc_store[slot].instruction_count == 0) {
		delete_proc(slot);
		proc_store[slot] = *proc;
		return slot;
	} else if (overwrite) {
		delete_proc(slot);
		proc_store[slot] = *proc;
		return slot;
	}
	return -1;
}

proc_t * get_proc(uint8_t slot) {
	if (slot >= 0 && slot < MAX_PROC_SLOT + 1) {
		return &proc_store[slot];
	}
	return NULL;
}

int * get_proc_slots() {
	int * slots = malloc((MAX_PROC_SLOT + 2) * sizeof(int));
	int count = 0;

	for (int i = 0; i < MAX_PROC_SLOT + 1; i++) {
		if (proc_store[i].instruction_count > 0) {
			slots[count++] = i;
		}
	}

	slots[count] = -1;  // Terminate the array with -1
	return slots;
}
