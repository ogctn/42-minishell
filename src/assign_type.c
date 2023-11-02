#include "../inc/minishell.h"

int which_operator(char *a)
{
	if(!ft_strcmp(a,"|"))
		return(2);
	else if(!ft_strcmp(a,"<"))
		return(2);
	else if(!ft_strcmp(a,"<<"))
		return(3);	
	else if(!ft_strcmp(a,">"))
		return(4);
	else if(!ft_strcmp(a,">>"))
		return (6);
	else
		return(2);
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
	else
		tmp->type = 0;
	while(next_data)
    {
        if(is_operate(*(next_data->content)))
			next_data->type = which_operator(next_data->content);
		else if(is_operate(*(tmp->content)))
			next_data->type = 0;
		else
			next_data->type = 1;
		next_data = next_data->next;
        tmp = tmp->next;
    }
}

