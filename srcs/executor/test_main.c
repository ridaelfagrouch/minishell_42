#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	// argc = 0;
	// argv = NULL;
	//envp = NULL;
	
	t_env_vars	*head = convert_env_vars_to_linked_list(envp);
	t_env_vars	*output;

	output = head;
	while (output)
	{
		printf("%s=%s\n", output->key, output->value);
		output = output->next;
	}
	printf("\n\n\n\n");
	export_cmd(head, "SOMETHING=nothing");
	export_cmd(head, NULL);
	return (0);
}