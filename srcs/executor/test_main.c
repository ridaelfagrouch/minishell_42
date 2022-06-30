#include "executor.h"
typedef struct s_cmds
{
	int		token;
	char	*data;
	char	*path;
	int		i;
	int		j;
	int		file_fd;
}	t_cmds;

int main(int argc, char **argv, char **envp)
{
	t_info	arr[5];
	int 	i = 0;


	while (i < 5)
	{
		arr[i].input = ""
		i++;
	}
	(void)argc;
	(void)argv;
	env_vars = conv_env(envp);
	execute_command(input, env_vars);
	return (0);
}

// ToDo:	Check commands exit status
// ToDo:	Check signal handling
// ToDo:	Check heredoc
// ToDo:	Check handle_execution function
// ToDo:	Check leaks
// ToDo:	Norm all the code 