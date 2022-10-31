#include "minishell.h"

int	init_env(char **env)
{
	t_data	*data;
	int		i;

	i = 0;
	data = get_data(NULL);
	while (env[i])
		i++;
	if (ft_calloc((void **)&data->env, i, sizeof(char *)))
		return (1);
	while (i--)
	{
		if (ft_strdup(data->env + i, env[i]))
			return (1);
	}
	return (0);
}

int add_env(char *str)
{
	int		i;
	t_data	*data;

	i = 0;
	data = get_data(NULL);
	while (is_in_charset(str[i], "="))
		i++;
	if (str[i] != '\0')
		return (1);
	i = 0;
	while (data->env[i])
		i++;
	if (ft_realloc((void **)&data->env,  sizeof(char *) * i, sizeof(char *) * (i + 1))
		|| ft_strdup(data->env + i, str))
		return (1);
	return (0);
}

int del_env(char *str)
{
	t_data	*data;
	char 	**last;
	int		pos_del;
	int 	i;
	int 	y;
	size_t	len;

	i  = 0;
	y = 0;
	pos_del = 0;
	len = ft_strlen(str);
	data = get_data(NULL);
	while (data->env[pos_del] && ft_strncmp(data->env[pos_del], str, len))
		pos_del++;
	if (!data->env[pos_del])
		return (1);
	last = data->env;
	if (ft_calloc((void **)&data->env, sizeof(char *), --len) )
		return (1);
	while (last[y])
	{
		if (y != pos_del)
			data->env[i++] = *last;
		y++;
	}
	del_malloc((void *)last);
	return (0);
}

int iter_env(size_t (*f)(char *, int))
{
	char	**current;
	t_data	*data;

	data = get_data(NULL);
	current = data->env;
	while (current)
	{
		if (f(*current, 1) < 0)
			return (1);
		current++;
	}
	return (0);
}