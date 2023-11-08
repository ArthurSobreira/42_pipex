/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:07:01 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/08 19:32:17 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char *cmd_name, char *envp[])
{
	size_t	env_index;
	size_t	path_index;
	char	**split;
	char	**split_path;
	
	if (*cmd_name == '\0')
		handle_error(4);
	env_index = 0;
	while ((envp[env_index]) && (ft_strncmp(envp[env_index], "PATH=", 5)))
		env_index++;
	
	split_path = ft_split(envp[env_index] + 5, ':');
	
	path_index = 0;
	while (split_path[path_index] != NULL)
	{
		ft_printf("%s/\n", split_path[path_index]);
		path_index++;
	}

	split = ft_split(cmd_name, SPACE);
	return (ft_strjoin("/usr/bin/", split[0]));
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
