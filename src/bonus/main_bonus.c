/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:08:19 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/10 13:35:25 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5)
		handle_error(1);
	else
	{
		pipex.commands = argc - 3;
		pipex.success = TRUE;
		start_io_files(&pipex, argv);
		get_commands(&pipex, argv, envp);
		execute_commands(&pipex);
		if (pipex.success == TRUE)
			clear_all(&pipex, 0);
	}
	return (0);
}
