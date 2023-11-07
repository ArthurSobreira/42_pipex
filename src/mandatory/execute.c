/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:01:15 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/07 16:42:28 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_commands(t_pipex *pipex)
{
	size_t	index;

	index = 0;
	while (index < pipex->commands)
	{
		if (index < pipex->commands - 1)
			if (pipe(pipex->fd_pipe) < 0)
				handle_error(2);
		pipex->commands_array[index].pid = fork();
		if (pipex->commands_array[index].pid < 0)
			handle_error(3);
		if (pipex->commands_array[index].pid == 0)
			exec_child_process(pipex, &pipex->commands_array[index]);
		close(pipex->fd_pipe[1]);
		index++;
	}
	waitpid(ANY_CHILD, NULL, 0);
	close(pipex->fd_pipe[0]);
	close(pipex->fd_input_file);
	close(pipex->fd_output_file);
}

void	exec_child_process(t_pipex *pipex, t_cmd *command)
{
	short	read_pipe;
	short	write_pipe;
	
	read_pipe = pipex->fd_pipe[0];
	write_pipe = pipex->fd_pipe[1];
	if (command->pros == INITIAL)
	{
		dup2(pipex->fd_input_file, STDIN_FILENO);
		close(read_pipe);
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
		execve(command->cmd, command->argv, command->envp);
	}
	else if (command->pros == FINAL)
	{
		dup2(pipex->fd_output_file, STDOUT_FILENO);
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
		close(write_pipe);
		execve(command->cmd, command->argv, command->envp);
	}
}
