/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:24 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/09 17:31:40 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start_io_files(t_pipex *pipex, char *argv[])
{
	char	*in_file;
	char	*out_file;

	in_file = argv[1];
	out_file = argv[pipex->commands + 2];
	start_input_file(pipex, in_file);
	start_output_file(pipex, out_file);
}

void	start_input_file(t_pipex *pipex, char *in_file)
{
	if (access(in_file, F_OK) != 0)
		handle_file_error(1);
	else if (access(in_file, R_OK) != 0)
		handle_file_error(2);
	else
	{
		pipex->fd_input_file = open(in_file, O_RDONLY);
		if (pipex->fd_input_file < 0)
			handle_file_error(3);
	}
}

void	start_output_file(t_pipex *pipex, char *out_file)
{
	pipex->fd_output_file = open(out_file, O_WRONLY | \
								O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_output_file < 0)
		handle_file_error(3);
}
