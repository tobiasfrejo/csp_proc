project('csp_proc', 'c', subproject_dir: 'lib', default_options: [
	'c_std=gnu11',
	'b_lto=false',
	'default_library=static',
])

csp_dep = dependency('csp', fallback : ['csp', 'csp_dep'])
param_dep = dependency('param', fallback : ['param', 'param_dep'])

csp_proc_inc = include_directories('include')

csp_proc_src = files([
	'src/proc_client.c',
	'src/proc_pack.c',
])

# Static & dynamic analysis
if get_option('proc_analysis') == true
	csp_proc_src += files([
		'src/proc_analyze.c',
	])
endif

# Slash shell / command-parser
slash_dep = []
if get_option('slash') == true
	slash_dep = dependency('slash', fallback : ['slash', 'slash_dep'], required: false)
	if slash_dep.found()
		csp_proc_src += files([
			'src/slash/slash_csp_proc.c',
		])
	endif
endif

if get_option('posix') == true and get_option('freertos') == true
    error('Cannot build for both POSIX and FreeRTOS (choose one max)')
endif

if get_option('posix') == false and get_option('freertos') == false
	error('Must build for either POSIX or FreeRTOS (choose one)')
endif

if get_option('posix') == true
	csp_proc_src += files([
		'src/platform/proc_memory_POSIX.c',
		'src/platform/proc_mutex_POSIX.c',
	])
endif

if get_option('freertos') == true
	csp_proc_src += files([
		'src/platform/proc_memory_FreeRTOS.c',
		'src/platform/proc_mutex_FreeRTOS.c',
	])
endif

# Default FreeRTOS-based runtime implementation
freertos_dep = []
if get_option('freertos') == true and get_option('proc_runtime') == true
	freertos_dep = dependency('freertos', fallback : ['freertos', 'freertos_dep'], required: false)
	if freertos_dep.found()
		csp_proc_src += files([
			'src/runtime/proc_runtime_instructions_common.c',
			'src/runtime/proc_runtime_instructions_FreeRTOS.c',
			'src/runtime/proc_runtime_FreeRTOS.c',
			'src/proc_analyze.c',
		])
	endif
	if get_option('proc_store_static') == false and get_option('proc_store_dynamic') == false
		error('FreeRTOS runtime requires a proc store (e.g. proc_store_dynamic=true)')
	endif
endif

# Default POSIX-based runtime implementation
posix_dep = []
if get_option('posix') == true and get_option('proc_runtime') == true
	csp_proc_src += files([
		'src/runtime/proc_runtime_instructions_common.c',
		'src/runtime/proc_runtime_instructions_POSIX.c',
		'src/runtime/proc_runtime_POSIX.c',
		'src/proc_analyze.c',
	])
	if get_option('proc_store_static') == false and get_option('proc_store_dynamic') == false
		error('POSIX runtime requires a proc store (e.g. proc_store_dynamic=true)')
	endif
endif

if get_option('proc_store_static') == true and get_option('proc_store_dynamic') == true
	error('Cannot build with multiple proc stores enabled (choose one max)')
endif

# Static store
if get_option('proc_store_static') == true
	csp_proc_src += files([
		'src/store/proc_store_static.c',
		'src/proc_server.c',  # proc server only makes sense with a proc store
	])
endif

# Dynamic store
if get_option('proc_store_dynamic') == true
	csp_proc_src += files([
		'src/store/proc_store_dynamic.c',
		'src/proc_server.c',  # proc server only makes sense with a proc store
	])
endif

# Configuration options
reserved_proc_slots = get_option('RESERVED_PROC_SLOTS')
max_proc_block_timeout_ms = get_option('MAX_PROC_BLOCK_TIMEOUT_MS')
min_proc_block_period_ms = get_option('MIN_PROC_BLOCK_PERIOD_MS')
max_proc_recursion_depth = get_option('MAX_PROC_RECURSION_DEPTH')
max_proc_concurrent = get_option('MAX_PROC_CONCURRENT')
max_instructions = get_option('MAX_INSTRUCTIONS')
max_proc_slot = get_option('MAX_PROC_SLOT')

if reserved_proc_slots != ''
    add_project_arguments('-DRESERVED_PROC_SLOTS=' + reserved_proc_slots, language : 'c')
endif
if max_proc_block_timeout_ms != ''
    add_project_arguments('-DMAX_PROC_BLOCK_TIMEOUT_MS=' + max_proc_block_timeout_ms, language : 'c')
endif
if min_proc_block_period_ms != ''
    add_project_arguments('-DMIN_PROC_BLOCK_PERIOD_MS=' + min_proc_block_period_ms, language : 'c')
endif
if max_proc_recursion_depth != ''
    add_project_arguments('-DMAX_PROC_RECURSION_DEPTH=' + max_proc_recursion_depth, language : 'c')
endif
if max_proc_concurrent != ''
    add_project_arguments('-DMAX_PROC_CONCURRENT=' + max_proc_concurrent, language : 'c')
endif
if max_instructions != ''
    add_project_arguments('-DMAX_INSTRUCTIONS=' + max_instructions, language : 'c')
endif
if max_proc_slot != ''
    add_project_arguments('-DMAX_PROC_SLOT=' + max_proc_slot, language : 'c')
endif

# Final library
csp_proc_lib = static_library('csp_proc',
	sources: [csp_proc_src],
	include_directories : csp_proc_inc,
	dependencies : [csp_dep, param_dep, slash_dep, freertos_dep],
	install : false
)

csp_proc_dep = declare_dependency(include_directories : csp_proc_inc, link_with : csp_proc_lib, dependencies : [csp_dep, param_dep])


# Tests
# NOTE: Requires "-Dslash:builtins=true -Dparam:list_dynamic=true"
if get_option('build_tests')
	criterion_dep = dependency('criterion', required : false)
	if not criterion_dep.found()
		error('Criterion not found (required for tests)')
	endif

	test_src = files([
		'src/slash/slash_csp_proc.c',

		'tests/test_client_server.c',
		'tests/test_proc_pack.c',
		'tests/test_slash_commands.c',
	])

	test_harness_inc = include_directories('tests/include')

	test_slash_dep = dependency('slash', fallback : ['slash', 'slash_dep'], required: false)

    run_tests_executable = executable(
        'run_tests', test_src, build_by_default : false,
        dependencies : [criterion_dep, csp_proc_dep, csp_dep, param_dep, test_slash_dep, freertos_dep],
        include_directories : test_harness_inc,
    )

    test('run_tests', run_tests_executable)
endif
