/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:23:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/05 00:02:56 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

typedef struct s_env
{
	char			*content;
	int				is_exported;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			*content;
	int				type;
	t_env			*env;
	struct s_data	*next;
}					t_data;

typedef struct s_path
{
	char	**sp_env;
	char	**sp_cmd;
	char	*full_path;
}			t_path;

void	ft_parser(char *str, t_data **total_line, t_env *env_list);
void	ft_split_2(char *str, t_data **total_line);
t_data	*ft_last(t_data *lst);
t_data	*ft_create(char *str);
int		ft_lstsize(t_data *lst);
void	list_add(char *str, t_data **total_line);
char	**ft_spc_split(char const *s);
int		is_operate(char s);
int		is_quote(char s);
int		in_quote(char *s);

void	mini_clear(t_env *env);
void	suppress_output(void);
void	sig_handler(int signal);

int		check_if_null(char *str);
int		is_missing_quoted(char *str);
int		is_there_a_slash(char *str);
void	free_data(t_data *d);

int		ft_strcmp(char *s1, char *s2);
int		is_buitin(char	*cmd);
int		file_or_dir_exists(char *path, int flag_case);

char	*ft_strjoin_null(char const *s1, char const *s2, void *freeable);
char	**split_env_path(t_env *env);
void	free_2d(char **d);
char	*path_finder(char *full_cmd, t_env *env);
void	get_default_env(t_env **env_list, char **env);
char	**env_to_double_arr(t_env *env);

t_env	*node_get_last(t_env *env);
t_env	*node_new(void *content);
void	node_add_back(t_env **lst, char *content);
void	init_env_all_data_nodes(t_data **d, t_env *env);
void	dup_env_list(t_env **dest_env, t_env *src_env);

char	**list_to_double_arr(t_data *d);
int		exec_simple(t_data *d);
void	count_char(char *read_line, char c, int *counter);
int		executer(t_data *data);
int		exec_builtin(t_data *data);

int		ft_echo(t_data *d);
void	print_env(t_env *env_list);
int		ft_env(t_data *data);
int		ft_exit(t_data *d);
int		ft_pwd(void);
int		are_valid_params(t_data *d, char *cmd);
int		ft_unset(t_data *d);
char	*get_env_value(t_env *env, char *key);
void	set_env_value(t_env *env, char *key, char *value);
int		ft_cd(t_data *d);
int		ft_export(t_data *d);

#endif
