#include "minishell.h"

int	init_env(t_data *data, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	if (ft_calloc(&data->garbage, (void **)&data->env, i, sizeof(char *)))
		return (1);
	while (i--)
	{
		if (ft_strdup(data, data->env + i, env[i]))
			return (1);
	}
	return (0);
}

int add_env(t_data *data, char *str)
{
	int		i;

	i = 0;
	if (!is_in_charset(str, "="))
		return (1);
	while (data->env[i])
		i++;
	if (ft_realloc(&data->garbage, (void **)&data->env,  sizeof(char *) * i, sizeof(char *) * (i + 1))
		|| ft_strdup(data, data->env + i, str))
		return (1);
	return (0);
}

int del_env(t_data *data, char *str)
{
	char 	**last;
	int		pos_del;
	int 	i;
	int 	y;
	size_t	len;

	i  = 0;
	y = 0;
	pos_del = 0;
	len = ft_strlen(str);
	while (data->env[pos_del] && ft_strncmp(data->env[pos_del], str, len))
		pos_del++;
	if (!data->env[pos_del])
		return (1);
	last = data->env;
	if (ft_calloc(&data->garbage, (void **)&data->env, sizeof(char *), --len) )
		return (1);
	while (last[y])
	{
		if (i != y)
			data->env[i++] = *last;
		y++;
	}
	del_malloc(&data->garbage, (void *)last);
	return (0);
}