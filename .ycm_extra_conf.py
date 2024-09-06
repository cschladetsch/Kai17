def Settings( **kwargs ):
    return {
        'flags': [
            '-Wall',
            '-Wextra',
            '-Werror',
            '-x', 
			'c++',
            '-std=c++17',

            '-I', '.',
            '-I', './include',
            '-I', '/usr/include',
        ],
    }

