#include "garbage.h"

int	create_element(t_malloc **new, void *data)
{
	t_malloc	*element;

	element = malloc(sizeof(t_malloc));
	if (!element)
		return (1);
	element->next = NULL;
	element->content = data;
	*new = element;
	return (0);
}

int	add_front(void *content)
{
	t_malloc	*current;
	t_malloc	**root;
	t_malloc	*element;

	if (create_element(&element, content))
		return (1);
	root = &(get_data(NULL)->garbage);
	current = *root;
	if (!current)
	{
		*root = element;
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
	if (current->content)
		free(current->content);
	current->content = NULL;
	if (current)
		free(current);
	current = NULL;
	return (0);
}

int	del_malloc(void *element)
{
	int			pos;
	t_malloc	*current;
	t_malloc	*tmp;
	t_malloc	**root;

	if (!element)
		return (1);
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

int	free_all(void)
{
	t_malloc	*current;
	t_malloc	*tmp;
	t_malloc	**root;

	root = &(get_data(NULL)->garbage);
	current = *root;
	while (current)
	{
		tmp = current->next;
		free_node(current);
		current = tmp;
	}
	*root = NULL;
	return (0);
}