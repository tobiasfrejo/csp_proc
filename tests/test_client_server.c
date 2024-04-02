#include <criterion/criterion.h>
#include <csp_proc_test/csp_network_test_harness.h>

Test(csp_network, test_network_init) {
	cr_assert(node1_fixture->iface->addr == 1);
	cr_assert(node2_fixture->iface->addr == 2);
	cr_assert(node3_fixture->iface->addr == 3);
}
