project('atomenv', 'cpp', 'c')

vag = dependency('libvag')
helen3d = dependency('helen3d')
helencore = dependency('helencore')

# Run the version and hash generator
hash_script = find_program('get_hash.sh')

gen_src = custom_target('commit-output',
                        input : ['src/commit.h.pre'],
                        output : ['commit.h'],
                        command : [hash_script, '@INPUT@', '@OUTPUT@'],
                        build_by_default: true,
                        build_always_stale: true)

executable('atom_environment', gen_src, 
'src/main.cpp', 
'src/Environment.cpp', 
cpp_args: ['-std=c++11'], dependencies : [ 
vag,
helen3d,
helencore
], install: true)

