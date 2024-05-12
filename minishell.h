/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:27:49 by nkarpeko          #+#    #+#             */
/*   Updated: 2024/01/30 21:14:00 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <unistd.h>

extern int			g_exit_code;

typedef struct s_parseexec
{
	char			*q;
	char			*eq;
	int				tok;
}					t_parseexec;

typedef struct s_process_heredoc
{
	char			*substr;
	int				s_idx;
	int				idx;
}					t_process_heredoc;

struct				s_echo_args
{
	char			*buf;
	char			**custom_environ;
	int				*idx;
	int				*inside_sing_quotes;
	int				newline;
};

struct				s_cmd
{
	int				type;
	int				flag;
};

struct				s_execcmd
{
	int				type;
	char			**argv;
	int				argc;
	int				max_args;
};

struct				s_redircmd
{
	int				type;
	struct s_cmd	*cmd;
	char			*file;
	int				mode;
	int				fd;
};

struct				s_pipecmd
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
};

typedef struct s_quotes
{
	char			*var_value;
	int				i;
	int				memory_allocated;
	int				in_double_quotes;
	int				in_single_quotes;
	bool			in_q;
}					t_quotes;

typedef struct s_quotes3
{
	char			*var_val;
	char			*result;
	int				s_idx;
	int				ch_va1;
	int				ch_va2;
}					t_quotes3;

int					runcmd(struct s_cmd *cmd, char ***env);
int					fork1(void);
int					exec_cmd(struct s_cmd *cmd, char ***custom_environ);
int					get_token(char **ps, char *es, char **q, char **eq);
int					peek(char **ps, char *es, char *toks);
char				*mkcopy(char *s, char *es);
struct s_cmd		*execcmd(void);
struct s_cmd		*parsecmd(char *s, char **custom_env);
struct s_cmd		*redircmd(struct s_cmd *subcmd, char *file, int type);
struct s_cmd		*pipecmd(struct s_cmd *left, struct s_cmd *right);
struct s_cmd		*parseredirs(struct s_cmd *cmd, char **ps, char *es);
struct s_cmd		*parsepipe(char **ps, char *es, char **custom_env);
struct s_cmd		*parseexec(char **ps, char *es, char **custom_env);
char				*concat_args(char **args);
int					builtins(char **buf_args, int argc, char ***env);
void				env(char **env);
char				*custom_getenv(char *name, char **custom_environ,
						bool full_str);
void				ft_cd(char *buf, char **custom_environ);
void				unset(char **buf_arr, char ***custom_environ);
char				*find_command_in_path(char *command, char **custom_environ);
void				free_cmd(struct s_cmd *command);
void				redirect_cmd(struct s_redircmd *rcmd,
						char ***custom_environ);
void				pipe_command(struct s_pipecmd *pcmd, char ***env);
char				*read_and_trim_line(char *buf);
void				ctrl_c_handler(int sig);
bool				is_blank(const char *buf);
void				echo(char **buf);
void				handle_variable_expansion(char *buf, char **custom_environ,
						int *idx);
void				process_variables(char *buf, char **custom_environ,
						int *idx, int inside_sing_quotes);
void				process_echo_command(struct s_echo_args *args);
char				**create_unset_arr(char *buf, char **custom_environ);
void				export(char **buf_arr, char ***custom_environ, int argc);
void				pwd(void);
char				*check_for_pipes(char *buffer);
int					builtin_exit(char *buf);
char				*parseexec_arg_process(char *q, char *eq,
						char **custom_env);
int					handle_double_redirect_left(struct s_redircmd *rcmd,
						char ***custom_environ);
void				calc_len_with_vars_middleware(int *idx, int *str_len,
						char *substr);
char				*return_variable(char *buf, int *idx, int *new_buf_idx,
						char **custom_environ);
void				process_delimeter(char *delimiter, char *quote_type);
int					double_redirect_left(struct s_redircmd *rcmd,
						char **custom_environ);
int					check_error(char *cmd);
char				**clone_env(char **env);
int					quotes_env_errors_exit_code(int *is_itoa, char *arg, int *i,
						char **var_value);
int					re_e_v_ch_em(char *var_value, char **result, int *j);
char				*handle_env_var(char *arg, int *i, int *memory_allocated,
						char **envp);
int					calculate_buf_var_code_error(char **arg, int *i, int *size);
int					calculate_buffer_size(char *arg, char quote_type,
						bool in_quotes, char **envp);
int					calculate_buf_if1(t_quotes *vars, char quote_type,
						char *arg);
void				calculate_buf_var_val(char **var_value, int *size,
						int memory_allocated);
char				*check_for_quotes(char *buffer);
char				*quotes_env_errors_return(char **result, int i);
char				*handle_all_quotes(char *arg, char **envp);

#endif
