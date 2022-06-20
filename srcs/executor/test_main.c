#include "executor.h"

int main(int argc, char **argv, char **envp)
{
	int	d_stdout;
	int	err;
	int	new_output_fd;

	new_output_fd = open("file", );
	d_stdout = dup(STDOUT_FILENO);
	if (d_stdout < 0)
		return (-1);
	err = dup2(new_output_fd, STDOUT_FILENO);
	if (err < 0)
		return (-1);
	return (0);
}
