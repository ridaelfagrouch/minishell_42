/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foundpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 08:46:49 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/24 15:53:30 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	free_split(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

/* -------------------------------------------------------------------------- */

void	check_path_cmd(t_data *data, char *av)
{
	if ((av[0] != '.' && av[0] != '/'))
	{
		while (data->path_split[data->i])
		{
			data->ptr = ft_strjoin(data->path_split[data->i], "/");
			data->final_path = ft_strjoin(data->ptr, data->cmd);
			free(data->ptr);
			data->check_access = access(data->final_path, X_OK | F_OK);
			if (data->check_access == 0)
				break ;
			else
				free(data->final_path);
			data->i++;
		}
		free_split(data->path_split);
	}
	else
	{
		data->final_path = ft_strdup(data->cmd);
		data->check_access = access(data->cmd, X_OK | F_OK);
	}
}

/* -------------------------------------------------------------------------- */

char	*found_path(t_data *data, char *av)
{
	check_path_cmd(data, av);
	if (data->check_access != 0)
	{
		printf("command not found\n");
		return (NULL);
	}
	if (ft_strchr(av, ' ') != 0)
		free(data->cmd);
	return (data->final_path);
}

/* -------------------------------------------------------------------------- */

int	check_cmd(t_data *data, char *av)
{
	if (ft_strchr(av, ' ') != 0 && (av[0] != '.' || av[0] != '/'))
	{ 
		data->cmd_split = ft_split(av, ' ');
		if (data->cmd_split[0] == NULL)
		{
			printf("command not found!\n");
			return (1);
		}
		data->cmd = ft_strdup(data->cmd_split[0]);
		free_split(data->cmd_split);
	}
	else
		data->cmd = av;
	return (0);
}

/* -------------------------------------------------------------------------- */

char	*get_path(char *av)
{
	t_data	*data;
	char	*tmp1;
	
	data = (t_data *) malloc(sizeof(t_data));
	data->i = 0;
	data->path = NULL;
	data->cmd_split = NULL;
	tmp1 = ft_strdup(av);
	tmp1 = ft_space(tmp1);
	if (ft_strchr(tmp1, SPACE_) || ft_strchr(tmp1, ' ') == NULL)
		av = remove_dq_sq(av);
	if (check_cmd(data, av))
		return (NULL);
	data->path = getenv("PATH");
	if (data->path == NULL)
	{
		printf("command not found!\n");
		return (NULL);
	}
	data->path_split = ft_split(data->path, ':');
	data->i = 0;
	return (found_path(data, av));
}

/* -------------------------------------------------------------------------- */
