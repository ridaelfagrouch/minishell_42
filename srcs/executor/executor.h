/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/03 17:13:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* ------------------------------- LIBRARIES -------------------------------- */
# include "../../minishell.h"

/* --------------------------------- MACROS --------------------------------- */

/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ ENUMs ----------- //

// ----------- STRUCTs ---------- //

/* --------------------------------- PROTOTYPES ----------------------------- */
t_env_vars	*get_env_var(char *varname, t_env_vars *env_head);
t_env_vars	*conv_env(char **envp);
void		free_env_linked_list(t_env_vars *head);
char		**split_env_vars_path_var(void);
int			init_node(char *input, t_env_vars **head);

int			export_cmd(char **input, t_env_vars *env_head);
int			cd_cmd(char **input, t_env_vars *env_head);
int			pwd_cmd(char **input, t_env_vars *env_head);
int			unset_cmd(char **input, t_env_vars *env_head);
int			env_cmd(char **input, t_env_vars *env_head);
int			echo_cmd(char **input, t_env_vars *env_head);
int			exit_cmd(char **input, t_env_vars *env_head);

int			print_sorted_env(t_env_vars *env_head);

#endif
