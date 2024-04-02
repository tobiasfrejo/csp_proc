#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <csp_proc_test/slash_test_harness.h>

Test(proc_slash_commands, commands_parse) {
	int result = proc_slash_command("proc new");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc new");

	result = proc_slash_command("proc block a == b 1");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc block a == b");

	result = proc_slash_command("proc ifelse a == b 2");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc ifelse a == b");

	result = proc_slash_command("proc noop 3");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc noop");

	result = proc_slash_command("proc set a 1 4");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc set a 1");

	result = proc_slash_command("proc unop a ++ b");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc unop a ++ b");

	result = proc_slash_command("proc binop a + b c 5");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc binop a + b c");

	result = proc_slash_command("proc call 1");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc call 1");

	result = proc_slash_command("proc pop 2");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc pop");

	result = proc_slash_command("proc size");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc size");

	result = proc_slash_command("proc list");
	cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc list");

	// result = proc_slash_command("proc slots");
	// cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc slots");

	// result = proc_slash_command("proc push 42");
	// cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc push 42");

	// result = proc_slash_command("proc pull 42");
	// cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc pull 42");

	// result = proc_slash_command("proc del 42");
	// cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc del 42");

	// result = proc_slash_command("proc run 1");
	// cr_assert_eq(result, SLASH_SUCCESS, "Failed on command: proc run 1");
}
