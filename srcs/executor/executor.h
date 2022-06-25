/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:11:47 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/22 19:22:37 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* ------------------------------- LIBRARIES -------------------------------- */
# include "../../minishell.h"

/* --------------------------------- MACROS --------------------------------- */
// ERROR Messages
# define EXIT_ERR	"numeric argument required"
# define CHDR_ERR	""
# define PWDR_ERR	""
# define XPRT_ERR	""
# define ENVR_ERR	""
# define ECHO_ERR	""
# define UNST_ERR	""

# define TRUE	1
# define FALSE	0

# define BUILT_INS	"echo cd pwd export unset env exit"
/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ ENUMs ----------- //

typedef enum e_pipe_stat
{
	NO_PIPE,
	TO_PIPE,
	FROM_PIPE,
}	t_pipe_stat;

// ----------- STRUCTs ---------- //

typedef struct s_shell_metadata
{
	t_env_vars	*env_head;
	int			last_exit_status;
}	t_shell_metadata;

/* --------------------------------- PROTOTYPES ----------------------------- */
// env_init_2nd.c
int		set_default_pwd(t_env_vars **head);
int		set_shell_lvl(t_env_vars **head);
void	free_env_linked_list(t_env_vars *head);
void	free_env(t_env_vars *head);

// env_init_1st.c
t_env_vars	*conv_env(char **envp);
int			process_env_var(t_env_vars **head, char *env_var);

// builtin_cmds
int			cd_cmd(char **input, t_env_vars **env_head);
int			echo_cmd(char **input, t_env_vars **env_head);
int			export_cmd(char **input, t_env_vars **env_head);
int			unset_cmd(char **input, t_env_vars **env_head);
int			env_cmd(char **input, t_env_vars **env_head);
int			pwd_cmd(char **input, t_env_vars **env_head);
void		exit_cmd(char **input, t_env_vars **env_head);

// exec_cmds.c
int			execute_command(t_node *node, t_env_vars **env_vars);

// exec_misc.c
t_env_vars	*get_env_var(char *varname, t_env_vars *env_head);
void		print_err(char *cmd, char *input, char *msg);

// redirect_exec.c
int			reset_stds_fd(void);
int			redirect_input(int new_input_fd);
int			redirect_output(int new_output_fd);
int			store_stds(void);

void	free_two_dim_arr(char **sorted_env);

#endif
