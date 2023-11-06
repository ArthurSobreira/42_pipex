/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:08:19 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/06 11:45:26 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		handle_error(1);
	else
	{
		start_io_files(&pipex, argv);
		ft_printf("fd_input_file: %d\n", pipex.fd_input_file);
		ft_printf("fd_output_file: %d\n", pipex.fd_output_file);
	}
	(void)argv;
	(void)envp;
	return (0);
}
