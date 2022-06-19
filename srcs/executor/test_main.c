#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	t_env_vars	*new_envp;
	char		*cmd1[3] = {"env", NULL, NULL};
	//char		*cmd2[3] = {"cd", "/Users/mnaimi/Desktop", NULL};
	//char		*cmd3[3] = {"pwd", "", NULL};

	argc = 0;
	argv = NULL;
	new_envp = conv_env(envp);
	execute_command(cmd1, new_envp);
	//execute_command(cmd2, new_envp);
	//execute_command(cmd3, new_envp);
	return (0);
}
