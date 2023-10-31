/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:23:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/01 01:23:51 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define  MINISHELL_H

#include <termios.h>

#include "../lib/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_data
{
	char			*content;
	int				type;
	struct s_data	*next;
}					t_data;

typedef struct s_path
{
	char	**sp_env;
	char	**sp_cmd;
	char	*full_path;
}			t_path;

void 	ft_parser(char *str,t_data **total_line);
void 	ft_split_2(char *str, t_data **total_line);
t_data	*ft_last(t_data *lst);
t_data	*ft_create(char *str);
int		ft_lstsize(t_data *lst);
char	**ft_spc_split(char const *s);
int 	is_operate(char s);
int 	is_quote(char *s);

void	suppress_output(void);
void	sig_handler(int signal);

int		check_if_null(char *str);
int		is_missing_quoted(char *str);
void	free_data(t_data *d);

int		ft_strcmp(char *s1, char *s2);
int		is_buitin(char	*cmd);

char	*ft_strjoin_null(char const *s1, char const *s2, void *freeable);
char	**split_env(char **env);
void	free_2d(char **d);
char	*path_finder(char *full_cmd, char **env);

char	**list_to_double_arr(t_data *d);
void	exec_simple(t_data *d, char **env);
void	count_char(char *read_line, char c, int *counter);
int		executer(t_data *data, char **env);


#endif
