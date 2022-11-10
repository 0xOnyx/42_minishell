#include "minishell.h"

int	init_env(char **env)
{
	t_data	*data;
	int		i;

	i = 0;
	data = get_data(NULL);
	while (env[i])
		i++;
	if (ft_calloc((void **)&(data->env), i + 1, sizeof(char *)))
		return (1);
	while (i--)
	{
		if (ft_strdup(data->env + i, env[i]))
			return (1);
	}
	return (0);
}

static int	get_pos_env(char ***res, char *name)
{
	char	**current;
	t_data	*data;
	size_t	len;

	len = ft_strlen(name);
	data = get_data(NULL);
	current = data->env;
	while (*current)
	{
		if (strncmp(*current, name, len) == 0)
		{
			*res = current;
			return (0);
		}
		current++;
	}
	return (1);
}

static int	is_current_env(char *str)
{
	char	*current;
	char	**tmp;
	char	*res;
	int		i;
	int		y;

	i = 0;
	while (is_in_charset(str[i], "="))
		i++;
	current = ft_substr(str, 0, i - 1);
	if (get_pos_env(&tmp, current))
		return (0 * del_malloc(current));
	y = 0;
	while (is_in_charset(str[y], "="))
		y++;
	if (str[y] != '\0')
		ft_strjoin(&res, str, "=");
	else
		res = str;
	ft_strdup(tmp, res);
	if (str[y] != '\0')
		del_malloc(res);
	del_malloc(current);
	del_malloc(tmp);
	return (1);
}

int	add_env(char *str)
{
	int		i;
	int		y;
	char	*res;
	t_data	*data;

	y = 0;
	data = get_data(NULL);
	if (is_current_env(str))
		return (0);
	while (is_in_charset(str[y], "="))
		y++;
	if (str[y] != '\0')
		ft_strjoin(&res, str, "=");
	else
		res = str;
	i = 0;
	while (data->env[i])
		i++;
	if (ft_realloc((void **)&data->env, sizeof(char *) * i, sizeof(char *) * (i + 1))
		|| ft_strdup(data->env + i, res))
		return (1);
	if (str[y] != '\0')
		del_malloc(res);
	return (0);
}

int	del_env(char *str)
{
	t_data	*data;
	char	**last;
	int		pos_del;
	int		i;
	int		y;

	i = 0;
	y = 0;
	pos_del = 0;
	data = get_data(NULL);
	while (data->env[pos_del] && ft_strncmp(data->env[pos_del], str, ft_strlen(str)))
		pos_del++;
	if (!data->env[pos_del])
		return (1);
	last = data->env;
	if (ft_calloc((void **)&data->env, sizeof(char *), ft_strlen(str) - 1))
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

int	iter_env(int (*f)(char *, int))
{
	char	**current;
	t_data	*data;
	int		i;

	i = 0;
	data = get_data(NULL);
	current = data->env;
	while (current[i])
	{
		if (f(current[i], i) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	get_env(char **res, char *name)
{
	char	*pos;
	char	**current;
	t_data	*data;
	size_t	len;

	len = ft_strlen(name);
	data = get_data(NULL);
	current = data->env;
	while (*current)
	{
		if (strncmp(*current, name, len) == 0
			&& (*current)[len] == '=')
		{
			if (ft_strchr(&pos, *current, '='))
				return (1);
			*res = pos + 1;
			return (0);
		}
		current++;
	}
	return (1);
}
