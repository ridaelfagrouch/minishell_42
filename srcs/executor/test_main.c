#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	char *input[3] = {"/bin/ls", "", NULL};
	t_env_vars *env_vars;

	(void)argc;
	(void)argv;
	env_vars = conv_env(envp);
	execute_command(input, env_vars);
	return (0);
}
