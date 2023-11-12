/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:16:48 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/12 15:16:48 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	here_doc(t_pipex *pipex)
{
	char	*line;
	int		pipe_fd[2];

	line = NULL;
	if (pipe(pipe_fd) < 0)
		handle_error(2);
	while (1)
	{
		ft_putstr_fd("pipex: \033[34;3mhere_doc\033[0m> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	pipex->fd_input_file = pipe_fd[0];
}
