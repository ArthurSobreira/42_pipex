/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_files_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:24 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/12 15:52:03 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	start_io_files(t_pipex *pipex, char *argv[])
{
	char	*in_file;
	char	*out_file;

	in_file = argv[1];
	out_file = argv[pipex->commands + 2];
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		pipex->commands--;
		pipex->cmd_index++;
		pipex->has_heredoc = TRUE;
		pipex->limiter = argv[2];
		out_file = argv[pipex->commands + 3];
	}
	start_input_file(pipex, in_file);
	start_output_file(pipex, out_file);
}

void	start_input_file(t_pipex *pipex, char *in_file)
{
	if (pipex->has_heredoc == TRUE)
		here_doc(pipex);
	else if (pipex->has_heredoc == FALSE)
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
}

void	start_output_file(t_pipex *pipex, char *out_file)
{
	if (pipex->has_heredoc == TRUE)
	{
		pipex->fd_output_file = open(out_file, O_WRONLY | \
								O_CREAT | O_APPEND, 0644);
		if (pipex->fd_output_file < 0)
			handle_file_error(3);
	}
	else if (pipex->has_heredoc == FALSE)
	{
		pipex->fd_output_file = open(out_file, O_WRONLY | \
								O_CREAT | O_TRUNC, 0644);
		if (pipex->fd_output_file < 0)
			handle_file_error(3);	
	}
}
