#include "../../inc/minishell.h"

int which_operator(char *a)
{
	if(!ft_strcmp(a,"|"))
		return(1);
	else if(!ft_strcmp(a,"<"))
		return(2);
	else if(!ft_strcmp(a,"<<"))
		return(3);	
	else if(!ft_strcmp(a,">"))
		return(4);
	else if(!ft_strcmp(a,">>"))
		return (5);
	else
		return(0);
}

void assign_type(t_data **total_line)
{
    t_data  *tmp;
	t_data  *next_data;

	tmp = (*total_line);
	next_data = tmp->next;
	if(!tmp)
		return;
	if(is_operate(*(tmp->content)))
		tmp->type = which_operator(next_data->content);
	while(next_data)
    {
		next_data->type = which_operator(next_data->content);
		next_data = next_data->next;
        tmp = tmp->next;
    }
}

