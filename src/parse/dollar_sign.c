#include "../../inc/minishell.h"

static char is_editable(char *str, char c)
{
	int i;
	char a;

	i = 0;
	while(str[i])
	{
		if(is_quote(str[i]))
		{
			a = str[i];
			i++;
			while (str[i] && str[i] != a)
			{
				if(str[i] == c && a != '\'' && str[i+1] && (ft_isalnum(str[i+1]) || str[i+1] == '_' || str[i+1] == '?'))
					return(i);
				i++;
			}
		}
		else if(str[i] == c && str[i+1] && (ft_isalnum(str[i+1]) || str[i+1] == '_' || str[i+1] == '?'))
			return(i);
		i++;
	}
	return(-1);
}

static int find_after_dolar(char *str)
{
	int i;
	i = is_editable(str,'$') + 1;
	if(str[i] == '?')
		return(i+1);
	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return(i);
}
static int is_env_var(char *str, t_env *env)
{
	int i;
	char *new;

	if (!env)
		return(0);
	i = is_editable(str,'$') + 1;
	if(str[i] == '?')
		return(2);
	new = ft_strjoin(str,"=");
	i = 0;
	while(env)
	{
		if(!ft_strncmp(new,env->content,ft_strlen(new)))
		{
			free(new);
			return(1);
		}
		env = env->next;
	}
	free(new);
	return(0);
}

char *re_create_content(char *str,t_env *env)
{
	char *new_str;
	char *var;
	char *b;
	int start;
	char *a;

	new_str = ft_substr(str,0,is_editable(str,'$'));
	start = find_after_dolar(str);
	var = ft_substr(str,is_editable(str,'$')+1,start-is_editable(str,'$')-1);
	if(is_env_var(var,env))
	{
		if(is_env_var(var,env)==2)
		{
			b = ft_itoa(0);
			new_str = ft_strjoin_null(new_str, b, new_str);
			free(b);
		}
		else
			new_str = ft_strjoin_null(new_str, get_env_value(env, var), new_str);
	}
	a = ft_substr(str,start,ft_strlen(str)-start);
	new_str = ft_strjoin_null(new_str,a,new_str);
	return(free(a), free(var), new_str);
}

void env_variable(t_data **data,t_env *env)
{
	char *a;
	t_data *tmp;
	if (!(*data))
		return;
	tmp = (*data);
	while(tmp)
	{
		if(is_editable(tmp->content,'$') != -1)
		{
			a = re_create_content(tmp->content,env);
			free(tmp->content);
			tmp->content = a;
		}
		else
			tmp = tmp->next;
	}
}
