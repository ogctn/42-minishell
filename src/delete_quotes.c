#include "../inc/minishell.h"

void re_create_quote(char *str, char **new, int i)
{
    int start;
    char a;

    start = i;
    while(str[i] && !is_quote(str[i]))
        i++;
    *new = ft_strjoin(*new, ft_substr(str,start,i-start));
    a = str[i];
    i++;
    start = i;
    while (str[i] && str[i] != a)
        i++;
    *new = ft_strjoin(*new, ft_substr(str,start,i-start));
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
    *new = ft_strjoin(*new, ft_substr(str,start,i-start));
}


void delete_quotes(t_data **data)
{
    t_data *tmp;
    char *new;

    tmp = (*data);
    while(tmp)
    {
        new = ft_strdup("");
        if(in_quote(tmp->content))
        {
            re_create_quote(tmp->content,&new,0);
            free(tmp->content);
            tmp->content = new;
        }
        tmp = tmp->next;
    }
}
