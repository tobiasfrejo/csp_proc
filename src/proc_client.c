#include <csp_proc/proc_client.h>

int proc_transaction(
	csp_packet_t * packet,
	response_callback_t response_callback,
	void * callback_arg,
	int host,
	int timeout) {
	csp_conn_t * conn = csp_connect(packet->id.pri, host, PROC_PORT_SERVER, 0, CSP_O_CRC32);
	if (conn == NULL) {
		printf("proc transaction failure\n");
		csp_buffer_free(packet);
		return -1;
	}

	csp_send(conn, packet);
	if (timeout == -1) {  // TODO: does this make sense?
		printf("proc transaction failure\n");
		csp_close(conn);
		return -1;
	}

	int result = -1;
	while ((packet = csp_read(conn, timeout)) != NULL) {
		int end = ((packet->data[0] & PROC_FLAG_END_MASK) == PROC_FLAG_END);

		if (response_callback != NULL && (packet->data[0] & PROC_FLAG_ERROR_MASK) == 0) {
			if (response_callback(packet, callback_arg) != 0) {
				printf("proc transaction response callback failure\n");
				break;
			}
		}

		csp_buffer_free(packet);

		if (end) {
			result = packet->data[0] & PROC_FLAG_ERROR_MASK;
			break;
		}
	}

	csp_close(conn);
	return result;
}

int proc_del_request(uint8_t proc_slot, int host, int timeout) {
	csp_packet_t * packet = csp_buffer_get(0);
	if (packet == NULL)
		return -2;

	packet->data[0] = PROC_DEL_REQUEST;
	packet->data[0] |= PROC_FLAG_END;
	packet->data[1] = proc_slot;
	packet->id.pri = CSP_PRIO_HIGH;
	packet->length = 2;

	return proc_transaction(packet, NULL, NULL, host, timeout);
}

int unpack_proc_callback(csp_packet_t * packet, void * arg) {
	proc_t * procedure = (proc_t *)arg;
	return unpack_proc_from_csp_packet(procedure, packet);
}

int proc_pull_request(proc_t * procedure, uint8_t proc_slot, int host, int timeout) {
	csp_packet_t * packet = csp_buffer_get(0);
	if (packet == NULL)
		return -2;

	packet->data[0] = PROC_PULL_REQUEST;
	packet->data[0] |= PROC_FLAG_END;
	packet->data[1] = proc_slot;
	packet->id.pri = CSP_PRIO_HIGH;
	packet->length = 2;

	int ret = proc_transaction(packet, unpack_proc_callback, procedure, host, timeout);
	if (ret != 0) {
		printf("Failed to unpack procedure from packet\n");
	}
	return ret;
}

int proc_push_request(proc_t * procedure, uint8_t proc_slot, int host, int timeout) {
	csp_packet_t * packet = csp_buffer_get(0);
	if (packet == NULL)
		return -2;

	pack_proc_into_csp_packet(procedure, packet);

	packet->data[0] = PROC_PUSH_REQUEST;
	packet->data[0] |= PROC_FLAG_END;
	packet->data[1] = proc_slot;
	packet->id.pri = CSP_PRIO_HIGH;

	return proc_transaction(packet, NULL, NULL, host, timeout);
}

int process_slots_response(csp_packet_t * packet, void * arg) {
	uint8_t * slots = ((uint8_t **)arg)[0];
	uint8_t * slot_count = ((uint8_t **)arg)[1];

	*slot_count = packet->length - 1;
	for (int i = 0; i < *slot_count; i++) {
		slots[i] = packet->data[1 + i];
	}

	return 0;
}

int proc_slots_request(uint8_t * slots, uint8_t * slot_count, int host, int timeout) {
	csp_packet_t * packet = csp_buffer_get(0);
	if (packet == NULL)
		return -2;

	packet->data[0] = PROC_SLOTS_REQUEST;
	packet->data[0] |= PROC_FLAG_END;
	packet->length = 1;
	packet->id.pri = CSP_PRIO_NORM;

	void * callback_arg[] = {slots, slot_count};
	int ret = proc_transaction(packet, process_slots_response, callback_arg, host, timeout);
	if (ret != 0) {
		return ret;
	}

	return ret;
}

int proc_run_request(uint8_t proc_slot, int host, int timeout) {
	csp_packet_t * packet = csp_buffer_get(0);
	if (packet == NULL)
		return -2;

	packet->data[0] = PROC_RUN_REQUEST;
	packet->data[0] |= PROC_FLAG_END;
	packet->data[1] = proc_slot;
	packet->id.pri = CSP_PRIO_HIGH;
	packet->length = 2;

	return proc_transaction(packet, NULL, NULL, host, timeout);
}
