/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:01:15 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/09 17:15:34 by arsobrei         ###   ########.fr       */
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
		free(pipex->commands_array[index].cmd);
		if (pipex->commands_array[index].argv)
			free_split(pipex->commands_array[index].argv);
		close(pipex->fd_pipe[1]);
		index++;
	}
	waitpid(ANY_CHILD, NULL, WNOHANG);
	close(pipex->fd_pipe[0]);
}

void	exec_child_process(t_pipex *pipex, t_cmd *command)
{
	short	read_pipe;
	short	write_pipe;

	read_pipe = pipex->fd_pipe[0];
	write_pipe = pipex->fd_pipe[1];
	if (command->proc_type == INITIAL)
	{
		dup2(pipex->fd_input_file, STDIN_FILENO);
		close(read_pipe);
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
		if (execve(command->cmd, command->argv, command->envp) < 0)
			handle_error(CMD_NOT_FOUND);
	}
	else if (command->proc_type == FINAL)
	{
		dup2(pipex->fd_output_file, STDOUT_FILENO);
		close(write_pipe);
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
		if (execve(command->cmd, command->argv, command->envp) < 0)
			handle_error(CMD_NOT_FOUND);
	}
}
