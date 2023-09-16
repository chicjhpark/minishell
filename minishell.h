/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:30:53 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/10 00:31:03 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <termios.h>
# include <signal.h>
# include "libft.h"

# define ERROR	-1

int	g_stat;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				print_check;
	struct s_env	*next;
}	t_env;

typedef struct s_set
{
	struct termios	org_term;
	struct termios	new_term;
	int				org_stdin;
	int				org_stdout;
}t_set;

typedef struct s_proc
{
	t_env	*env_lst;
	t_list	*data;
	t_list	*cmd;
	t_list	*limiter;
	int		infile;
	int		outfile;
	int		pip_flg;
	int		status;
}t_proc;

t_env	*env_dup_check(t_env *env_list, char *new_key);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_free_split(char **draw);
void	env_lstadd_back(t_env **lst, t_env *new,
			char *key, char *value);
t_env	*env_set(char **envp);
void	cd_error(int err, char *arg);
void	ft_cd(char **buf, t_env *env_list);
void	ft_env(t_env *env_list);
int		unset_key_syntax_check(char *s);
void	ft_unset(char **dbuf, t_env **env_list);
char	*read_value_of_key(t_env *env_list, char *key);
int		ft_echo(char **buf);
void	ft_pwd(void);
int		export_key_syntax_error(char *s);
int		export_key_syntax_check(char *s);
void	reset_env_print_check(t_env *env_list);
void	print_env_in_order(t_env *env_list);
void	ft_export(char **dbuf, t_env *env_list, char **splits, t_env *temp);
int		valid_exit_arg(char	*arg);
int		exit_numeric_arg_cal(char *arg);
void	exit_extra_cases(int c, char *s);
void	ft_exit(char **dbuf);

int		error_msg(char *msg);
void	*ft_free(char *p);
void	*ft_free2(char **p);
char	*ft_strntrim(char *s, char *set, int n);
char	*ft_strndup(char *s, int n);

void	init_set(t_set *set, t_env **env, char **envp);
void	reset_set(t_set *set);
void	reset_stdio(t_set *set);
void	init_set2(t_set *set, char ***envp, t_env *env);

int		split_token(char *input, t_list **token);
int		split_rest_token(char *input, t_list **token);
int		split_pipe_token(char *input, int i, t_list **token);
int		split_space_token(char *input, int i, t_list **token);
int		split_redirection_token(char *input, int i, t_list **token);

int		find_valid_quot_point(char *data, int start);
int		find_env_var_token(char *data, int start, int end);
int		find_valid_env_var_point(char *data);
int		check_token(t_list *token);
char	*my_strtrim(char *data, int start, int end);

int		parse_pipe_token(t_list *token, t_env *env, char **envp);
int		parse_process(t_proc *proc, t_env *env, char **envp);
int		parse_last_process(t_proc *proc, t_env *env, char **envp);
int		parse_data(t_proc *proc, t_list *data);
int		parse_std_inout_redirection(t_proc *proc, t_list *data, char *temp);

char	*expand_data(t_proc *proc, char *data);
char	*del_small_quot_token(char *data, int start, char **new_data);
char	*expand_env_var(t_proc *proc, char *data, int start, char **new_data);

int		heredoc(char *limiter);
void	handle_heredoc(t_list *token);

int		handle_command(t_proc *proc, t_list *cmd, char **envp);
int		handle_last_command(t_proc *proc, t_list *cmd, char **envp);
char	**split_command(t_list *cmd);

int		check_builtin_command(t_list *cmd);
void	execute_builtin_command(t_proc *proc, char **exe);
void	ft_replace_line(int var_stat);
void	ft_handler(int status);

char	*parse_pre_env_var(char *data, int start, char *new_data);
char	*expand_in_quot_utils(t_proc *proc, char *data, char **new_data);

int		ft_env_lstsize(t_env *lst);
char	**convert_env_lst_to_dp(t_env *env);

#endif
