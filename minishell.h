/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:33:01 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/25 16:05:24 by jaehpark         ###   ########.fr       */
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
	char			**input;
	int				infile;
	int				outfile;
	char			*limiter;
	int				num_pipe;
}					t_set;

int		error_msg(char *msg);
void	free_set(t_set *set);
void	init_set(t_set *set);

#endif
