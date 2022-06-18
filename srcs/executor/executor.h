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
// env_init_1st.c
t_env_vars	*conv_env(char **envp);
int			set_shell_lvl(t_env_vars **head);
int			set_default_pwd(t_env_vars **head);
int			set_default_pwd(t_env_vars **head);
int			set_default_env_vars(t_env_vars **head);

// env_init_2nd.c
t_env_vars	*get_last_env_node(t_env_vars *head);
int			overwrite_key_value(char *input, t_env_vars **head, char *sep);
void		add_node_to_env(t_env_vars *node, t_env_vars **head);
int			add_key_only(char *input, t_env_vars **head);
void		free_env(t_env_vars *head);

// env_init_3rd.c
int			add_key_value(char *input, t_env_vars **head, char *sep);
int			append_value(char *input, t_env_vars **head, char *sep);
int			init_node(char *input, t_env_vars **head);
char		*get_cwd_env_var(void);

// builtin_cmds
int			cd_cmd(char **input, t_env_vars *env_head);
int			echo_cmd(char **input, t_env_vars *env_head);
int			export_cmd(char **input, t_env_vars *env_head);
int			unset_cmd(char **input, t_env_vars *env_head);
int			env_cmd(char **input, t_env_vars *env_head);
int			pwd_cmd(char **input, t_env_vars *env_head);
void		exit_cmd(char **input, t_env_vars *env_head);

// exec_cmds.c
int			execute_non_builtin(char **input, t_env_vars *head);
int			execute_command(char **input, t_env_vars *env_vars);

// exec_misc.c
t_env_vars	*get_env_var(char *varname, t_env_vars *env_head);

#endif
