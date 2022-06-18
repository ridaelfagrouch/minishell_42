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


#endif
