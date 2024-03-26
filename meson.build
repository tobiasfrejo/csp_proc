project('csp_proc', 'c')

csp_dep = dependency('csp', fallback : ['csp', 'csp_dep'])
param_dep = dependency('param', fallback : ['param', 'param_dep'])

csp_proc_inc = include_directories('include')

csp_proc_src = files([
	'src/proc_client.c',
    'src/proc_pack.c',
    'src/proc_runtime_FreeRTOS.c',
    'src/proc_server.c',
    'src/proc_store.c',
])

slash_dep = []
if get_option('slash') == true
	slash_dep = dependency('slash', fallback : ['slash', 'slash_dep'], required: false)
	if slash_dep.found()
		csp_proc_src += files([
			'src/slash/slash_csp_proc.c',	
		])
	endif
endif

csp_proc_lib = static_library('csp_proc',
	sources: [csp_proc_src],
	include_directories : csp_proc_inc,
	dependencies : [csp_dep, slash_dep, param_dep],
	install : false
)

csp_proc_dep = declare_dependency(include_directories : csp_proc_inc, link_with : csp_proc_lib)
