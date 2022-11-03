#include "includers.h"


static int	get_prompt(char buff[MAX_PROMPT])
{
	char	*content_prompt[25];
	int		i;

	i = 0;
	ft_bzero(content_prompt, sizeof(char *) * 25);
	if (ft_strdup(&content_prompt[0], "\xF0\x9F\x94\xA5\x1b[91m ")
		|| ft_strdup(&content_prompt[1], "MINISHELL")
		|| ft_strdup(&content_prompt[2], " \x1b[97m\xF0\x9F\x94\xA5\t\xf0\x9f\x91\x89 ")
		|| ft_strdup(&content_prompt[3], "\x1b[32m[\x1b[97m ")
		|| get_pwd(&content_prompt[4])
		|| ft_strdup(&content_prompt[5], " \x1b[32m]\x1b[97m")
		|| ft_strdup(&content_prompt[6], " $ "))
		return (1);
	while (content_prompt[i])
	{
		if (ft_strlcat(buff, content_prompt[i], MAX_PROMPT) > MAX_PROMPT)
			return (1);
		del_malloc(content_prompt[i]);
		i++;
	}
	return (0);
}

static int	prompt(char **line)
{
	char 	buff[MAX_PROMPT];

	char 	*current_line;
	ft_bzero(buff, MAX_PROMPT);
	if (get_prompt(buff))
		return (1);
	current_line = readline(buff);
	if (!current_line)
		return (1);
	if (current_line && *current_line)
		add_history(current_line);
	*line = current_line;
	return (0);
}

static int kill_current_process(void)
{
	//kill();
	return (0);
}

static void	exit_handler(int sign)
{
	if (sign == SIGINT || sign == SIGQUIT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int 	minishell(void)
{
	t_command	*command;
	t_data		*data;
	char		*line;

	data = get_data(NULL);
	signal(SIGINT, &exit_handler);
	signal(SIGQUIT, &exit_handler);
	while (!prompt(&line))
	{
		//command = parse(line);
		//TEST
		command = calloc(sizeof(t_command),10);
		command[0].command = line;
		command[0].arguments = calloc(sizeof(char **), 3);
		command[0].arguments[0] = "-l";
		command[0].arguments[1] = NULL;
		command[0].stdin[0] = 0;
		command[0].stdout[1] = 1;
		command[0].stderr[1] = 2;
		command[0].last = 1;
		command[0].status = 0;
		command[1].command = NULL;
		data->command = command;

		if (exec_command())
			perror("Error:");
	};
	return (0);
}