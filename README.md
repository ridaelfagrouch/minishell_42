# minishell_42

 - The objective of this project is to create a simple shell, like an own little bash.
 It is the first group project in the 42 core curriculum.
  - Minishell will introduce you to the world of shells, which provide a convenient text interface to interact with your system. Shells might seem very easy to understand but have very specific and defined behaviour in almost every single case, most of which will need to be handled properly.

## Contributors

- Rida el fagrouch 	:   42login => `rel-fagr`, github => [ridaelfagrouch](https://github.com/ridaelfagrouch)
 - Mohamed Amin naimi : 	42login => `mnaimi`, github => [The-Intruder](https://github.com/The-Intruder)

 ## Features

### Basics:
- History of previous entered commands
- Search and launch the right executable (based on the `PATH` variable, using a relative or an absolute path)
- Environment variables (`$` followed by a sequence of characters) expand to their values
- Wildcards `*` in the current working directory
- `ctrl-C`, `ctrl-D` and `ctrl-\` behave like in bash
- `’` (single quotes - prevent from interpreting meta-characters in quoted sequence)
- `"` (double quotes - prevent from interpreting meta-characters in quoted sequence except for $)
- `$?` expands to the last exit status
- `|` connect cmds or groups with pipes; output of a cmd is connected to the input of the next cmd via a pipe

### Builtins:
- `echo` with option -n
- `cd`
- `pwd` without options
- `export` without options
- `unset` without options
- `env` without options
- `exit [exit_status]` without options

### Redirections:
- `< file` Redirecting Input
- `<< limiter` Here Documents
- `> file` Redirecting Output
- `>> file` Appending Redirected Output

## How to use?

 1. ``` bash
    git clone git@github.com:ridaelfagrouch/minishell_42.git && cd minishell_42
    ```
 1.  `make`  
 2.  `./minishell`
 3.  Run your commands