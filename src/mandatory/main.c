/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:08:19 by arsobrei          #+#    #+#             */
/*   Updated: 2023/12/11 12:50:11 by arsobrei         ###   ########.fr       */
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
		pipex.commands = argc - 3;
		pipex.success = TRUE;
		start_io_files(&pipex, argv);
		get_commands(&pipex, argv, envp);
		execute_commands(&pipex);
		if (pipex.success == FALSE)
			clear_all(&pipex, 42);
		clear_all(&pipex, 0);
	}
	return (0);
}
