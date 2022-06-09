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
# include <stdlib.h>
# include "../../minishell.h"

/* --------------------------------- MACROS --------------------------------- */

/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ ENUMs ----------- //

// ----------- STRUCTs ---------- //

/* --------------------------------- PROTOTYPES ----------------------------- */
t_env_vars	*conv_env(char **envp);
void		free_env_linked_list(t_env_vars *head);
char		**split_env_vars_path_var(void);
int			init_node(char	*env_var, t_env_vars *node);

int			export_cmd(t_env_vars *env_head, char *key_value);
int			pwd_cmd(t_env_vars *env_head);
#endif
