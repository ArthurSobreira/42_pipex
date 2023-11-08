/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:07:01 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/08 12:14:15 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_commands(t_pipex *pipex, char *argv[], char *envp[])
{
	size_t	index;
	char	**args;

	(void)argv;
	args = (char **)malloc(sizeof(char *) * 3);
	if (!argv)
		handle_error(4);
	pipex->commands_array = (t_cmd *)malloc(sizeof(t_cmd) * pipex->commands);
	if (!pipex->commands_array)
		handle_error(4);
	index = 0;
	while (index < pipex->commands)
	{
		if (index == 0)
		{
			pipex->commands_array[index].pid = -1;
			pipex->commands_array[index].pros_type = INITIAL;
			pipex->commands_array[index].cmd = "/usr/bin/cat";
			pipex->commands_array[index].argv = NULL;
			pipex->commands_array[index].envp = envp;
		}
		else if (index == 1)
		{
			args[0] = "grep";
			args[1] = "teste";
			args[2] = NULL;
			pipex->commands_array[index].pid = -1;
			pipex->commands_array[index].pros_type = FINAL;
			pipex->commands_array[index].cmd = "/usr/bin/grep";
			pipex->commands_array[index].argv = args;
			pipex->commands_array[index].envp = envp;
		}
		index++;
	}
}
