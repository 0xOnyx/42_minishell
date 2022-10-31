#include "garbage.h"

int	create_element(void *data)
{
	t_malloc	*new;
	t_malloc	**element;

	element = &(get_data(NULL)->garbage);
	new = malloc(sizeof(t_malloc));
	if (!new)
		return (1);
	new->next = NULL;
	new->content = data;
	*element = new;
	return (0);
}

int	add_front(t_malloc *element)
{
	t_malloc	*current;
	t_malloc	**root;

	root = &(get_data(NULL)->garbage);
	current = *root;
	if (!current)
	{
		*root  = element;
		return (0);
	}
	while (current->next)
		current = current->next;
	current->next = element;
	return (0);
}

int	get_id_malloc(void *element)
{
	int			i;
	t_malloc	*root;

	i = 0;
	root = get_data(NULL)->garbage;
	while (root)
	{
		if (root->content == element)
			return (i);
		root = root->next;
		i++;
	}
	return (-1);
}

t_malloc	*get_malloc(void *element)
{
	t_malloc	*root;

	root = get_data(NULL)->garbage;
	while (root)
	{
		if (root->content == element)
			return (root);
		root = root->next;
	}
	return (NULL);
}

int	free_node(t_malloc *current)
{
	free(current->content);
	free(current);
	return (0);
}

int	del_malloc(void *element)
{
	int			pos;
	t_malloc	*current;
	t_malloc	*tmp;
	t_malloc	**root;

	root = &(get_data(NULL)->garbage);
	pos = get_id_malloc(element);
	current = *root;
	if (pos < 0)
		return (1);
	if (pos == 0)
	{
		free_node(current);
		*root = NULL;
		return (0);
	}
	while (--pos > 0)
		current = current->next;
	tmp = current->next->next;
	free_node(current->next);
	current->next = tmp;
	return (0);
}

int	free_all()
{
	t_malloc	*current;
	t_malloc	*last;
	t_malloc	**root;

	root = &(get_data(NULL)->garbage);
	current = *root;
	last = current;
	while (last)
	{
		last = current->next;
		free_node(current);
	}
	*root = NULL;
	return (0);
}