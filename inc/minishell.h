/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:23:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/17 04:26:56 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include "../lib/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>

# define MINISHELL "\e[5m\e[48;5;175;52m miniHELL \e[25m\e[100;114m--> \e[0m"

typedef struct s_env
{
	char			*content;
	int				*exit_code;
	struct s_env	*next;
}					t_env;

typedef struct s_redir
{
	int		out_fd;
	int		out_flag;
	char	*input_name;
	int		in_flag;
}	t_redir;

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
	char	*full_path;
}			t_path;

int		ft_parser(char *str, t_data **total_line, t_env *env_list);
char	**ft_spc_split(char const *s);
void	ft_split_2(char *str, t_data **total_line);
int		find_end_1(int *start, const char *s, int *end, char c);

void	assign_type(t_data **total_line);
int		which_operator(char *a);
int		operator_err_control(t_data *data);

void	env_variable(t_data **data, t_env *env);
void	delete_quotes(t_data **data);

t_data	*ft_last(t_data *lst);
t_data	*ft_create(char *str);
void	list_add(char *str, t_data **total_line);
int		ft_lstsize(t_data *lst);

int		is_operate(char s);
int		is_quote(char s);
int		in_quote(char *s);

void	mini_clear(t_env *env);
void	get_signals(void);

int		check_if_null(char *str);
int		is_missing_quoted(char *str, t_env *env);
int		is_there_a_slash(char *str);
void	free_data(t_data *d);

int		ft_strcmp(char *s1, char *s2);
int		is_builtin(char	*cmd);
int		file_or_dir_exists(char *path, int flag_case);

char	*ft_strjoin_null(char const *s1, char const *s2, void *freeable);
char	**split_env_path(t_env *env);
void	free_2d(char **d);
char	*path_finder(char *full_cmd, t_env *env);
void	get_default_env(t_env **env_list, char **env, int *ercode);
char	**env_to_double_arr(t_env *env);
int		env_size(t_env *env);

t_env	*node_get_last(t_env *env);
t_env	*node_new(void *content, int *ercode);
void	node_add_back(t_env **lst, char *content);
void	init_env_all_data_nodes(t_data **d, t_env *env);
void	dup_env_list(t_env **dest_env, t_env *src_env);

char	**data_to_double_arr(t_data *d);
int		exec_simple(t_data *d);
int		count_pipes(t_data *d);
int		executer(t_data *data);
int		exec_builtin(t_data *data);
void	update_pipeline(t_data **d);

int		ft_echo(t_data *d);
void	print_env(t_env *env_list);
int		ft_env(t_data *data);
int		ft_exit(t_data *d);
int		ft_pwd(void);
int		is_valid_unset_parameter(char *content);
int		is_valid_export_parameter(char *content);
int		is_env_exist(t_env *env, char *content);
void	update_env_content(t_env **env, char *new);
int		ft_unset(t_data *d);
char	*get_env_value(t_env *env, char *key);
void	set_env_value(t_env *env, char *key, char *value);
int		ft_cd(t_data *d);
int		are_valid_cd_params(t_data *d);
int		ft_export(t_data *d);
void	env_swap(t_env *a, t_env *b, int *swap_flag);
int		find_len_content(char *content);

int		redir_in(t_data **head, t_data *d, int default_fds[2]);
int		redir_out(t_data **head, t_data *current);
void	copy_default_fd(int *default_in, int *default_out);
void	restore_defaults(int default_fds[2]);

#endif
