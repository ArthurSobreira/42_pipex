/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:08:19 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/07 17:20:06 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_commands(t_pipex *pipex)
{
	size_t	index;

	pipex->commands_array = (t_cmd *)malloc(sizeof(t_cmd) * pipex->commands);
	if (!pipex->commands_array)
			handle_error(4);
	index = 0;
	while (index < pipex->commands)
	{
		write(0, NULL, 0);
		if (index == 0)
		{
			pipex->commands_array[index].pid = -1;
			pipex->commands_array[index].pros = INITIAL;
			pipex->commands_array[index].cmd = "/usr/bin/cat";
			pipex->commands_array[index].argv = NULL;
			pipex->commands_array[index].envp = NULL;
		}
		else if (index == 1)
		{
			pipex->commands_array[index].pid = -1;
			pipex->commands_array[index].pros = FINAL;
			pipex->commands_array[index].cmd = "/usr/bin/grep";
			pipex->commands_array[index].argv = (char *[]){"grep", "teste", NULL};
			pipex->commands_array[index].envp = NULL;
		}
		index++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		handle_error(1);
	else
	{
		start_io_files(&pipex, argv);
		pipex.commands = argc - 3;
		get_commands(&pipex);
		
		// pipex.commands_array = (t_cmd[]){
		// 	{-1, INITIAL, "/usr/bin/cat", NULL, NULL},
		// 	{-1, FINAL, "/usr/bin/grep", ((char *[]){"grep", "teste", NULL}), NULL}
		// };

		execute_commands(&pipex);
		free(pipex.commands_array);
		handle_error(0);
		(void)envp;
	}
	return (0);
}
