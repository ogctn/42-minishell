/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:54:36 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/17 04:48:29 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_export_parameter(char *str)
{
	int	i;

	if (!str[0] || !(ft_isalpha(str[0]) || str[0] == '_'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (0);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	env_swap(t_env *a, t_env *b, int *swap_flag)
{
	char	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	*swap_flag = 1;
}

int	find_len_content(char *content)
{
	int	len;

	if (ft_strchr(content, '='))
		len = ft_strchr(content, '=') - content;
	else
		len = ft_strlen(content);
	return (len);
}

int	is_env_exist(t_env *env, char *content)
{
	int	len_to_equal;
	int	len_content;

	len_content = find_len_content(content);
	while (env)
	{
		if (ft_strchr(env->content, '='))
			len_to_equal = ft_strchr(env->content, '=') - env->content;
		else
			len_to_equal = ft_strlen(env->content);
		if (ft_strncmp(env->content, content, len_to_equal) == 0 \
			&& len_to_equal == len_content)
			return (1);
		env = env->next;
	}
	return (0);
}

void	update_env_content(t_env **env, char *new)
{
	int	len_to_equal;
	int	len_content;

	len_content = find_len_content(new);
	while (*env)
	{
		if (ft_strchr((*env)->content, '='))
			len_to_equal = ft_strchr((*env)->content, '=') - (*env)->content;
		else
			len_to_equal = ft_strlen((*env)->content);
		if (ft_strncmp((*env)->content, new, len_to_equal) == 0
			&& len_content == len_to_equal)
		{
			if (ft_strchr((*env)->content, '=') && !ft_strchr(new, '='))
				return ;
			free((*env)->content);
			(*env)->content = new;
			return ;
		}
		*env = (*env)->next;
	}
}
