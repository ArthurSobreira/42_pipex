/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:08:19 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/05 16:24:43 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	start_io_files(t_pipex *pipex, char *argv[])
{
	pipex->input_file = argv[1];
	pipex->output_file = argv[4];

	pipex->fd_input = open(pipex->input_file, O_RDONLY);
	if (pipex->fd_input < 0)
		handle_error(2);
	pipex->fd_output = open(pipex.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.fd_output < 0)
		handle_error(3);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		handle_error(1);
	else
	{
		start_io_files(pipex, argv);	
	}
	
	pipex.input_file = argv[1];
	pipex.output_file = argv[4];
	pipex.fd_input = open(pipex.input_file, O_RDONLY);

	(void)argv;
	(void)envp;
	return (0);
}
