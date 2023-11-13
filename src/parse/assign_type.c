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
	else if(!ft_strcmp(a,"||"))
		return (6);
	else
		return(0);
}

void assign_type(t_data **total_line)
{
	t_data  *tmp;

	tmp = (*total_line);
	if(!tmp)
		return;
	while(tmp)
	{
		tmp->type = which_operator(tmp->content);
		tmp = tmp->next;
	}
}

