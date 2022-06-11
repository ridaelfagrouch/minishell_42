/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foundpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 08:46:49 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/06/11 13:46:55 by rel-fagr         ###   ########.fr       */
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

//*************************found_path***************************

char	*found_path(t_data *data, char *av)
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
	if (data->check_access != 0)
	{
		printf("command not found\n");
		return (NULL);
	}
	free_split(data->path_split);
	if (ft_strchr(av, ' ') != 0)
		free(data->cmd);
	return (data->final_path);
}

//*************************check_cmd***************************

int	check_cmd(t_data *data, char *av)
{
	if (ft_strchr(av, ' ') != 0)
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

//************************get_path****************************

char	*get_path(char *av)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	data->i = 0;
	data->path = NULL;
	data->cmd_split = NULL;
	if (check_cmd(data, av))
		return (NULL);	
	data->path = getenv("PATH");
	if (data->path == NULL)
	{
		printf("command not found!\n");
		return (NULL);
	}
	data->path_split = ft_split(data->path, ':');
	// free(data->path);
	data->i = 0;
	return (found_path(data, av));
}
