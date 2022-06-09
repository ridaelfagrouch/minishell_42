#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	argc = 0;
	argv = NULL;
	// envp = NULL;
	int ret;
	t_env_vars *env_head;

	env_head = conv_env(envp);
	if (!env_head)
		return (-1);

	pwd_cmd(env_head);
	printf("%s\n", getenv("PWD"));
	printf("%s\n\n", getenv("OLDPWD"));
	ret = chdir("/Users/mnaimi/Desktop");
	pwd_cmd(env_head);
	printf("%s\n", getenv("PWD"));
	printf("%s\n", getenv("OLDPWD"));
	return (0);
}