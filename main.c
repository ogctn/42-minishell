/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:24:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/10/30 20:55:03 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_control(t_data **total_line)
{
	t_data *tmp_1;
	t_data *tmp_2;

	tmp_1 = *total_line;

	while (tmp_1)
	{
		if(*(tmp_1->content) == '|' || *(tmp_1->content) == '<' || *(tmp_1->content) == '>')
		{
			tmp_2=tmp_1->next;
			if(tmp_2 && *(tmp_1->content) == *(tmp_2->content))
			{
				tmp_2 = tmp_2->next;
				if(tmp_2 && (*(tmp_1->content) == *(tmp_2->content) || *(tmp_1->content) =='|'))
					printf("error 1\n");
			}
			else
			{
				if(tmp_2 && (*(tmp_2->content) == '|' || *(tmp_2->content) == '<' || *(tmp_2->content) == '>'))
					printf("error 2\n");
			}
		}
		tmp_1= tmp_1->next;

	}

}
//#################################################################################################
//#########################			[ADDED PART START]			###################################
//#################################################################################################

//---	TO HEADER	----
// typedef struct s_path
// {
// 	char	**sp_env;
// 	char	**sp_cmd;
// 	char	*full_path;
// }			t_path;

//		!!!		parse.c:81 -> after else statement add tmp->next->type = 1 for pipe and redirections		!!!

//			ft_strjoin	MODIFIED LIBFT FUNC			//
//				USED AT (ft)PATH_FINDER					//
// char	*ft_strjoin(char const *s1, char const *s2, void *freeable)
// {
// 	size_t	len;
// 	char	*ret;

// 	if (!s1 || !s2)
// 		return (0);
// 	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
// 	ret = (char *)malloc(len * sizeof(char));
// 	if (!ret)
// 		return (0);
// 	ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
// 	ft_strlcat(ret, s2, len);
// 	if (freeable)
// 		free(freeable);
// 	return (ret);
// }
//					END: ft_strjoin			//


int	check_if_null(char *str)
{
	if (str == NULL)
		exit(3);
	if (str[0] == '\0')
	{
		free(str);
		return (1);
	}
	return (0);
}

int	is_missing_quoted(char *str)
{
	unsigned int	i;
	char			quote;

	quote = 0;
	i = -1;
	while (str[++i])
	{
		if (quote == 0 && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
	}
	if (quote != 0)
	{
		printf("minishell$ parse error near `%c`\n", quote);
		//free(str);
	}
	return (quote != 0);	
}

void	count_char(char *read_line, char c, int *counter)
{
	int	i;

	i = -1;
	while (read_line[++i])
		if (read_line[i] == c)
			(*counter)++;
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-s2[i]);
}
int	is_buitin(char	*cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

char	**split_env(char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = ft_strnstr(env[i], "PATH=", 5);
		if (tmp)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	free_2d(char **l)
{
	int	i;

	i = 0;
	while (l[i])
		free(l[i++]);
	free(l);
}

char	*path_finder(char *full_cmd, char **env)
{
	t_path	path;
	int		i;

	path.sp_env = split_env(env);
	path.sp_cmd = ft_split(full_cmd, ' ');
	i = -1;
	while (path.sp_env[++i])
	{
		path.full_path = ft_strjoin(path.sp_env[i], "/", NULL);
		path.full_path = \
			ft_strjoin(path.full_path, path.sp_cmd[0], path.full_path);
		if (access(path.full_path, F_OK) == 0)
		{
			free_2d(path.sp_cmd);
			free_2d(path.sp_env);
			return (path.full_path);
		}
		free(path.full_path);
	}
	free_2d(path.sp_cmd);
	free_2d(path.sp_env);
	return (NULL);
}

int	ft_lstsize(t_data *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**list_to_double_arr(t_data *d)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_lstsize(d) + 1));
	ret[ft_lstsize(d)] = NULL;
	while (d)
	{
		ret[i++] = ft_strdup(d->content);
		d = d->next;
	}
	return (ret);
}

void prp(char **a)
{
	int i = 0;
	while (a[i])
		printf("%s\n", a[i++]);
}

void	exec_simple(t_data *d, char **env)
{
	char	**args;
	pid_t	pid;
	char 	*cmd_path;
	//int		builtin_flag;
	
	//builtin_flag = is_buitin(line);
	pid = fork();
	if (pid == 0)
	{
		args = list_to_double_arr(d);
		printf("-*---------*-\n");
		prp(args);
		printf("-*---------*-\n");
		execve(path_finder(args[0], env), args, env);
		exit(1);
	}
	wait(NULL);
}


int	executer(t_data *data, char **env)
{
	char *full_line;
	int	pipe_count;
	int	redir_count;
	int	redir_type;

	pipe_count = 0;
	//count_char(read_line, '|', &pipe_count);	// will be changed
	//if (pipe_count == 0)
	//{
		//if (redir_type == 0)
			exec_simple(data, env);
		// else if (redir_type == 1)
		// 	exec_redir_out(full_line, env);
		// else if (redir_type == 2)
		// 	exec_redir_in(full_line, env);
	//}
	//else
		//if (exec_pipe(full_line, env))
	//		return (-1);
	return (0);
}


void	printit(t_data *d)
{
	int i = 0;
	while (d)
	{
		printf("\neleman:%d --->\t%s\n", i, d->content);
		printf("type: %d\n", d->type);
		d = d->next;
		i++;
	}
}

void	free_data(t_data *d)
{
	t_data *tmp;

	if (!d)
		return ;
	while (d)
	{
		tmp = d->next;
		free(d->content);
		free(d);
		d = tmp;
	}
}

int main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*line;
	int 	i;
	
	if (ac != 1 || av[1] != NULL || !env) // to check if there is no argument
		return (1);
	while (1)
	{
		i = 0;
		if (line)
			free(line); // to free the line from the previous iteration
		line = readline("minishell$ ");
		if (!line) // to check if the line is empty
			exit(1);
		data = NULL;
		ft_parser(line, &data);
		printit(data);	// to print the linked list
		if (check_if_null(line) || is_missing_quoted(line)) // to check if there are missing quotes or null
			continue ; // to continue the loop if there are missing quotes or null
		add_history(line);
		executer(data, env); // to execute the command
		free_data(data); // to free the linked list
		//system("leaks minishell");  // cumulative leaks from ft_parser [NOT SURE]
	}
	return (0);
}
//#################################################################################################
//#########################			[ADDED PART END]			###################################
//#################################################################################################

