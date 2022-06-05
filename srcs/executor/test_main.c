#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	// argc = 0;
	// argv = NULL;
	//envp = NULL;
	
	t_env	*head = convert_env_to_linked_list(envp);
	t_env	*output;

	output = head;
	while (output)
	{
		printf("%s=", output->key);
		printf("%s\n", output->value);
		output = output->next;
	}
	printf("\n\n");
	export_var_to_env(head, "NAME=amine");
	export_var_to_env(head, "SOMETHING=nothing");
	output = head;
	while (output)
	{
		printf("%s=", output->key);
		printf("%s\n", output->value);
		output = output->next;
	}
	return (0);
}