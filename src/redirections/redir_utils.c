/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:12:20 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/17 11:45:22 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sig_exit_heredoc(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

void	heredoc_loop(char *content, int fd)
{
	char	*line;

	signal(SIGINT, &sig_exit_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, content, ft_strlen(content))
			&& ft_strlen(line) == ft_strlen(content))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	redir_in_continued(int type, char *path_here, int fd)
{
	if (type == 3)
		free(path_here);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
