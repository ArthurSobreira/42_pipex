/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:08:19 by arsobrei          #+#    #+#             */
/*   Updated: 2023/12/11 12:50:23 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	start_pipex(t_pipex *pipex, int argc);

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5)
		handle_error(1);
	else if (!ft_strncmp(argv[1], "here_doc", 8) && (argc < 6))
		handle_error(5);
	else
	{
		start_pipex(&pipex, argc);
		start_io_files(&pipex, argv);
		get_commands(&pipex, argv, envp);
		execute_commands(&pipex);
		if (pipex.success == FALSE)
			clear_all(&pipex, 42);
		clear_all(&pipex, 0);
	}
	return (0);
}

static void	start_pipex(t_pipex *pipex, int argc)
{
	pipex->commands = argc - 3;
	pipex->cmd_index = 2;
	pipex->success = TRUE;
	pipex->has_heredoc = FALSE;
}
