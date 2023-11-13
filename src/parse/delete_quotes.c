#include "../../inc/minishell.h"

void re_create_quote(char *str, char **new, int i)
{
	int start;
	char a;

	start = i;
	while(str[i] && !is_quote(str[i]))
	    i++;
	(*new) = ft_strjoin_null((*new), ft_substr(str,start,i-start),(*new));
	a = str[i];
	i++;
	start = i;
	while (str[i] && str[i] != a)
	    i++;
	*new = ft_strjoin_null(*new, ft_substr(str,start,i-start),(*new));
	i++;
	start = i;
	while (str[i])
	{
		if(is_quote(str[i]))
		{
			re_create_quote(str,new,start);
			return;
		}
		i++;
	}
	*new = ft_strjoin_null(*new, ft_substr(str,start,i-start),(*new));
}


void delete_quotes(t_data **data)
{
	t_data *tmp;
	char *new;

	if (!(*data))
		return;
	tmp = (*data);
	while(tmp)
	{
		if(in_quote(tmp->content))
		{
			new = ft_strdup("");
			re_create_quote(tmp->content,&new,0);
			free(tmp->content);
			tmp->content = new;
		}
		tmp = tmp->next;
	}
}
