/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:07:01 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/13 12:10:59 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_commands(t_pipex *pipex, char *argv[], char *envp[])
{
	size_t	index;
	size_t	cmd_index;

	pipex->commands_array = (t_cmd *)malloc(sizeof(t_cmd) * pipex->commands);
	if (!pipex->commands_array)
		handle_error(4);
	index = 0;
	cmd_index = 2;
	while (index < pipex->commands)
	{
		pipex->commands_array[index].pid = -1;
		pipex->commands_array[index].cmd = get_cmd_path(argv[cmd_index], envp);
		if (!ft_strchr(pipex->commands_array[index].cmd, '/'))
			pipex->success = FALSE;
		pipex->commands_array[index].argv = get_arguments(argv[cmd_index]);
		pipex->commands_array[index].envp = envp;
		if (index == 0)
			pipex->commands_array[index].proc_type = INITIAL;
		else if (index == (pipex->commands - 1))
			pipex->commands_array[index].proc_type = FINAL;
		cmd_index++;
		index++;
	}
}

char	*get_cmd_path(char *cmd_name, char *envp[])
{
	size_t	env_index;
	char	**split_path;
	char	*cmd;
	char	*with_path;

	cmd = get_cmd_name(cmd_name);
	with_path = NULL;
	env_index = 0;
	while ((envp[env_index]) && (ft_strncmp(envp[env_index], "PATH=", 5)))
		env_index++;
	split_path = ft_split(envp[env_index] + 5, TWO_POINTS);
	with_path = validate_path(cmd, split_path);
	if (!with_path)
		return (cmd);
	return (with_path);
}

char	*get_cmd_name(char *cmd_name)
{
	size_t	len_cmd;

	if (!cmd_name[0])
		return (ft_substr("cmd", 0, 3));
	len_cmd = 0;
	while ((*cmd_name != '\0') && (*cmd_name == SPACE))
		cmd_name++;
	while ((cmd_name[len_cmd] != '\0') && (cmd_name[len_cmd] != SPACE))
		len_cmd++;
	return (ft_substr(cmd_name, 0, len_cmd));
}

char	**get_arguments(char *argv)
{
	char	**split_args;
	size_t	args;

	split_args = ft_split(argv, SPACE);
	args = 0;
	while (split_args[args] != NULL)
		args++;
	if (args == 1)
	{
		free_split(split_args);
		return (NULL);
	}
	return (split_args);
}

char	*validate_path(char *cmd_name, char **split_path)
{
	size_t	index;
	char	*path;
	char	*with_path;

	index = 0;
	path = NULL;
	with_path = NULL;
	while (split_path[index] != NULL)
	{
		path = ft_strjoin(split_path[index], "/");
		with_path = ft_strjoin(path, cmd_name);
		free(path);
		if (access(with_path, F_OK | X_OK) == 0)
		{
			free_variables(cmd_name, split_path);
			return (with_path);
		}
		free(with_path);
		index++;
	}
	free_variables(NULL, split_path);
	return (NULL);
}
