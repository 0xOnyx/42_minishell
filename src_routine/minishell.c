#include "includers.h"

static int	get_prompt(char buff[MAX_PROMPT])
{
	char	*content_prompt[25];
	int		i;

	i = 0;
	ft_bzero(content_prompt, sizeof(char *) * 25);
	ft_strdup(&content_prompt[i++], "\xF0\x9F\x94\xA5\x1b[91m ");
	ft_strdup(&content_prompt[i++], "MINISHELL");
	ft_strdup(&content_prompt[i++], " \x1b[97m\xF0\x9F\x94\xA5\t\xf0\x9f\x91\x89 ");
	ft_strdup(&content_prompt[i++], "\x1b[32m[\x1b[97m ");
	get_pwd(&content_prompt[i++]);
	ft_strdup(&content_prompt[i++], " \x1b[32m]\x1b[97m");
	if (!get_git(&content_prompt[i + 1]))
	{
		ft_strdup(&content_prompt[i], "\x1b[32m[\x1b[96m ");
		ft_strdup(&content_prompt[i + 2], " \x1b[32m]\x1b[97m");
		i += 3;
	}
	ft_strdup(&content_prompt[i], " $ ");
	i = 0;
	while (content_prompt[i])
	{
		if (ft_strlcat(buff, content_prompt[i], MAX_PROMPT) > MAX_PROMPT)
			return (1);
		del_malloc(content_prompt[i++]);
	}
	return (0);
}

static int	prompt(char **line)
{
	char	buff[MAX_PROMPT];
	char	*current_line;

	ft_bzero(buff, MAX_PROMPT);
	if (get_prompt(buff))
		return (1);
	current_line = readline(buff);
	if (!current_line)
		return (1);
	if (*current_line)
		add_history(current_line);
	*line = current_line;
	return (0);
}
	//TODO: Update this for the new version
static int	kill_current_process(void)
{
//	t_command	*command;
//
//	command = &get_data(NULL)->command;
//	while (command && command->pid > 0)
//	{
//		kill(command->pid, SIGINT);
//		command++;
//	}
	return (0);
}

static void	exit_handler(int sign)
{
	if (sign == SIGINT || sign == SIGQUIT)
	{
		kill_current_process();
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	minishell(void)
{
	t_data		*data;
	char		*line;

	data = get_data(NULL);
	signal(SIGINT, &exit_handler);
	signal(SIGQUIT, &exit_handler);
	while (!prompt(&line))
	{
		printf("current line => {%s}\n", line);
		if (parser(line) || !data->lexical)
			ft_putstr_fd("Error: Command\n", 2);
		else if (exec_command())
			perror("Error:");
		free(line);
		printf("my pid in main is => %d\n", data->pid[0]);
	}
	return (0);
}
