#include "../inc/minishell.h"

static t_table	*create_table(char **ptr)
{
	t_table	*new;

	new = malloc(sizeof(t_table));
	new->command = ptr;
	new->next = NULL;
	return (new);
}

static int	tablesize(t_data *data)
{
	int	i;

	i = 0;
	while (data)
	{
        if(*(data->content) != '|')
        {
		    i++;
		    data = data->next;
        }
	}
	return (i);
}
static char **create_command(t_data *data)
{
    t_data *tmp;
    int size;
    int i;
    char **ptr;

    tmp = data;
    size = 0;
    i = 0;
    while (tmp && *(tmp->content) != '|')
    {
        size++;
        tmp = tmp->next;      
    }
    ptr = malloc(sizeof(char *)*(size+1));
    
    while(i<size)
    {
        ptr[i] = tmp->content;
        i++;
        tmp = tmp->next;
    }
    ptr[i] = '\0';
    return(ptr);
}

t_table *re_shape(t_data **data)
{
    t_data *tmp;
    t_table *tmp_table;
    t_table *command_table;
    int i;

    tmp = (*data);
    i = 0;

    command_table = create_table(create_command(tmp));
    while(tmp && *(tmp->content) != '|')
        tmp = tmp->next;
    tmp_table = command_table;
    
    while(i < pipe_count(*data))
    {
        tmp_table = tmp_table->next;
        tmp_table = create_table(create_command(tmp));
        while(tmp && *(tmp->content) != '|')
            tmp = tmp->next;
        i++;
    }
    return(command_table);
}
