/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:37:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 21:37:48 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
	Built-In vs Shell Programs

	Built-in commands are executed as a function.But it may fork first if you 
	use it in a pipeline '|', for example:
		$ cd / | echo 
	it forks and calls cd in the child. You can also notice this by how 
	the directory doesn't actually change.
*/

/* -------------------------------------------------------------------------- */

static void	print_env_vars(t_env_vars *env_head, bool is_env)
{
	t_env_vars	*node;

	node = env_head;
	while (node)
	{
		if (is_env && node->is_env_var)
			printf("%s=%s\n", node->key, node->value);
		else if (!is_env && !node->is_env_var)
		{
			printf("%s", node->key);
			if (node->value)
				printf("=\"%s\"", node->value);
			write(1, "\n", 1);
		}
		node = node->next;
	}
}

/* -------------------------------------------------------------------------- */

int	export_cmd(t_env_vars *env_head, char *key_value)
{
	t_env_vars	**tracer;
	t_env_vars	*node;

	node = NULL;
	if (key_value == NULL)
		return (print_env_vars(env_head, false), 0);
	tracer = &env_head;
	while ((*tracer)->next)
		tracer = &(*tracer)->next;
	node = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
	if (!node || init_node(key_value, node) != 0)
		return (free(node), -1);
	(*tracer)->next = node;
	return (0);
}

/*
	CMD RULES:

	If no keys are supplied, a list of keys of all exported variables is 
	displayed.

	The return status is zero unless an invalid option is supplied, one of 
	the keys is not a valid shell variable name.
*/

/* -------------------------------------------------------------------------- */

// Set CWD in env after changing directory

// int	cd_cmd(char *path)
// {
// 	char	*old_wd;

// 	old_wd
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 		return (-1);
// 	printf("%s\n", cwd);
// 	return (0);
// }



// stat("srcs", &stats);
// if (S_ISREG(stats.st_mode))
// 	printf("file is a Regular File");
// else if (S_ISDIR(stats.st_mode))
// 	printf("file is a Directory");
// else
// 	printf("Unknown Filetype");

/*
	CMD RULES:

	Change the current working directory to directory. If directory is not 
	supplied, the value of the HOME shell variable is used. Any additional 
	arguments following directory are ignored.

	If directory is ‘-’, it is converted to $OLDPWD before the directory 
	change is attempted.

	If ‘-’ is the first argument, and the directory change is successful, 
	the absolute pathname of the new working directory is written to the 
	standard output.

	???????????????????????????????????????????????????????????????????????????
	If the shell variable CDPATH exists, it is used as a search path: each 
	directory name in CDPATH is searched for directory, with alternative 
	directory names in CDPATH separated by a colon (‘:’). If directory begins 
	with a slash, CDPATH is not used.
	???????????????????????????????????????????????????????????????????????????

	The return status is zero if the directory is successfully changed, 
	non-zero otherwise.
*/

/* -------------------------------------------------------------------------- */

int	echo_cmd(char **input, bool n_flag)
{
	int	i;

	if (input == NULL)
		return (-1);
	i = 0;
	while (input[i])
		printf("%s ", input[i++]);
	if (n_flag == false)
		write(1, "\n", 1);
	return (0);
}

/*
	CMD RULES:

	Output the args, separated by spaces, terminated with a newline. The
	return status is 0 unless a write error occurs. If -n is specified, the
	trailing newline is suppressed.
	The xpg_echo shell option may be used to dynamically determine whether or
	not echo expands these escape characters by default. echo does not
	interpret -- to mean the end of options.
*/

t_env_vars	*get_env_var(t_env_vars *env_head, char *varname)
{
	t_env_vars	*node;

	node = env_head;
	while (node && ft_strcmp(node->key, varname) != 0)
		node = node->next;
	if (ft_strcmp(node->key, varname) != 0)
		return (NULL);
	return (node);
	
}

/* -------------------------------------------------------------------------- */

int	pwd_cmd(t_env_vars *env_head)
{
	char 		cwd[PATH_MAX];
	t_env_vars	*node;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (-1);
	node = get_env_var(env_head, "PWD");
	printf("Key: %s\n", node->key);
	if (node)
	{
		free(env_head->value);
		env_head->value = ft_strdup(cwd);
	}
	printf("%s\n", cwd);
	return (0);
}

/*
	CMD RULES:

	Print the absolute pathname of the current working directory. The return
	status is zero unless an error is encountered while determining the name
	of the current directory or an invalid option is supplied.
*/

/* -------------------------------------------------------------------------- */

// int	unset_cmd(char *path)
// {
// 	return (0);
// }

/*
	CMD RULES:

	If no options are supplied, each name refers to a variable; if there is
	no variable by that name, a function with that name, if any, is unset.
	Readonly variables and functions may not be unset. Some shell variables
	lose their special behavior if they are unset; such behavior is noted in
	the description of the individual variables. The return status is zero
	unless a name is readonly.
*/

/* -------------------------------------------------------------------------- */

int	env_cmd(t_env_vars *head, char *args)
{
	t_env_vars	*node;

	if (args == NULL)
	{
		node = head;
		while (node)
		{
			if (node->key && node->value)
				printf("%s=%s\n", node->key, node->value);
			node = node->next;
		}
	}
	return (0);
}

/*
	CMD RULES:

	Without any argument : print out a list of all environment variables.
*/

/* -------------------------------------------------------------------------- */

void	exit_cmd(int exit_status)
{
	exit(exit_status);
}

/*
	CMD RULES:

	Exit the shell, returning a status of n to the shell’s parent. If n is
	omitted, the exit status is that of the last command executed. Any trap
	on EXIT is executed before the shell terminates.
*/

/* -------------------------------------------------------------------------- */
