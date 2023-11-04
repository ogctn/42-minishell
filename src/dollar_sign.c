#include "../inc/minishell.h"

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
                if(str[i] == c && a != '\'' && str[i+1] && (ft_isalnum(str[i+1]) || str[i+1] == '_'))
                    return(i);
                i++;    
            }  
        }
        else if(str[i] == c && str[i+1] && (ft_isalnum(str[i+1]) || str[i+1] == '_'))
            return(i);
        i++;
    }
    return(-1);

}

static int find_after_dolar(char *str)
{
	int i;
	i = is_editable(str,'$') + 1;
	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return(i);
}
static int is_env_var(char *str, char **env)
{
    int i;
    char *new;

    new = ft_strjoin(str,"=");

    i = 0;
    while(env[i])
    {
        if(!ft_strncmp(new,env[i],ft_strlen(new)))
            return(1);
        i++;
    }
    return(0);
}

char *re_create_content(char *str,char **env)
{
    char *new_str;
    char *var;
    int i = 0;
    int start;
	start = find_after_dolar(str);
	new_str = ft_substr(str,0,is_editable(str,'$'));
    var = ft_substr(str,is_editable(str,'$')+1,start-is_editable(str,'$')-1);
	if(is_env_var(var,env))
        new_str = ft_strjoin(new_str,getenv(var));
    free(var);
	new_str = ft_strjoin(new_str,ft_substr(str,start,ft_strlen(str)-start));
    return(new_str);
}

void env_variable(t_data **data,char **env)
{
    char *a;
    t_data *tmp = (*data);
    while(tmp)
    {
        if(is_editable(tmp->content,'$') != -1)
        {
            a = re_create_content(tmp->content,env);
            free(tmp->content);
            tmp->content = a;
			printf("%s\n",tmp->content);
        }
		else
            tmp = tmp->next;
    
    }
}