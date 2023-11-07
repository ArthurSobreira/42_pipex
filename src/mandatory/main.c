/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:08:19 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/07 19:21:38 by arsobrei         ###   ########.fr       */
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
		// write(0, NULL, 0);
		if (index == 0)
		{
			//ft_printf("entrou1\n");
			pipex->commands_array[index].pid = -1;
			pipex->commands_array[index].pros = INITIAL;
			pipex->commands_array[index].cmd = "/usr/bin/cat";
			pipex->commands_array[index].argv = NULL;
			pipex->commands_array[index].envp = NULL;
		}
		else if (index == 1)
		{
			//ft_printf("entrou2\n");
			char **argv = (char **)malloc(sizeof(char *) * 3);
			if (argv != NULL)
			{
				argv[0] = "grep";
				argv[1] = "teste";
				argv[2] = NULL;
			}
			pipex->commands_array[index].pid = -1;
			pipex->commands_array[index].pros = FINAL;
			pipex->commands_array[index].cmd = "/usr/bin/grep";
			pipex->commands_array[index].argv = argv;
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

		ft_printf("argumentos: %s\n", pipex.commands_array[1].argv[1]);

		execute_commands(&pipex);
		free(pipex.commands_array[1].argv);
		free(pipex.commands_array);
		handle_error(0);
		(void)envp;
	}
	return (0);
}
