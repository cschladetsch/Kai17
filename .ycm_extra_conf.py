def Settings( **kwargs ):
    return {
        'flags': [
            '-Wall',
            '-Wextra',
            '-Werror',
            '-x', 'c++',
            '-std=c++11',
            # Add paths to header files
            '-I', '.',
            '-I', './include',
            '-I', './usr/lib/llvm-10/include/c++/v1/',

            # Add more flags as needed
        ],
    }

