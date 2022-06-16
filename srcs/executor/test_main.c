#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	int8_t	exit_value;
	argc = 0;
	argv = NULL;
	// envp = NULL;
	t_env_vars *env_head;

	env_head = conv_env(envp);
	print_sorted_env(env_head);
	init_node("OLDPWD", &env_head);
	print_sorted_env(env_head);
	return (0);
}
