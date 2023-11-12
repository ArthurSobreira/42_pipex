/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:08:19 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/12 12:38:57 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5)
		handle_error(1);
	else if (!ft_strncmp(argv[1], "here_doc", 8) && (argc < 6))
		handle_error(5);
	else
	{
		pipex.commands = argc - 3;
		pipex.success = TRUE;
		start_io_files(&pipex, argv);
		get_commands(&pipex, argv, envp);
		execute_commands(&pipex);
		if (pipex.success == TRUE)
			clear_all(&pipex, 0);
		clear_all(&pipex, -1);
	}
	return (0);
}
