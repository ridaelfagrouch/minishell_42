#include "executor.h"

int main(const int argc, const char **argv, const char **envp)
{
	// argc = 0;
	// argv = NULL;
	//envp = NULL;
	
	t_env	*output = convert_env_to_linked_list(envp);

	while (output)
	{
		printf("%s=", output->key);
		printf("%s\n", output->value);
		output = output->next;
	}
	return (0);
}