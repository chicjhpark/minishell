/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:33:01 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/04 20:29:06 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>

typedef struct s_set
{
	struct termios	org_term;
	struct termios	new_term;
	int				org_stdin;
	int				org_stdout;
}					t_set;

typedef struct s_cmd
{
	t_list	*lst;
	t_list	*head;
	char	*limiter;
	char	*infile;
	char	*outfile;
}					t_cmd;


int		error_msg(char *msg, char *type);
void	ft_free(char **ptr);
void	init_set(t_set *set);
void	divide_redirection(char *inputs, char *temp);
char	*sort_redirection(char *inputs);

#endif
