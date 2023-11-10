/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:01:15 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/10 17:18:54 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	execute_commands(t_pipex *pipex)
{
	size_t	index;

	index = 0;
	while (index < pipex->commands)
	{
		ft_printf("cmd: %s\n", pipex->commands_array[index].cmd);
		if (pipex->commands_array[index].argv)
			ft_printf("argv: %s\n", pipex->commands_array[index].argv[1]);
		ft_printf("proc_type: %d\n", pipex->commands_array[index].proc_type);
		ft_printf("pipe fd[0]: %d\n", pipex->fd_pipe[0]);
		ft_printf("pipe fd[1]: %d\n", pipex->fd_pipe[1]);
		ft_printf("\n");

		if (index < pipex->commands - 1)
			if (pipe(pipex->fd_pipe) < 0)
				handle_error(2);
		pipex->commands_array[index].pid = fork();
		if (pipex->commands_array[index].pid < 0)
			handle_error(3);
		if (pipex->commands_array[index].pid == 0)
			exec_child_process(pipex, &pipex->commands_array[index]);
		else
		{
			waitpid(pipex->commands_array[index].pid, NULL, 0);
			close(pipex->fd_pipe[1]);
		}
		free(pipex->commands_array[index].cmd);
		if (pipex->commands_array[index].argv)
			free_split(pipex->commands_array[index].argv);
		index++;
	}
	close(pipex->fd_pipe[0]);
}

void	exec_child_process(t_pipex *pipex, t_cmd *command)
{
	if (command->proc_type == INITIAL)
		initial_process(pipex, command);
	else if (command->proc_type == INTERMEDIATE)
		intermediate_process(pipex, command);
	else if (command->proc_type == FINAL)
		final_process(pipex, command);
}

void	initial_process(t_pipex *pipex, t_cmd *command)
{
	short	read_pipe;
	short	write_pipe;

	read_pipe = pipex->fd_pipe[0];
	write_pipe = pipex->fd_pipe[1];

	ft_printf("pipe fd[0]: %d\n", read_pipe);
	ft_printf("pipe fd[1]: %d\n", write_pipe);
	
	dup2(pipex->fd_input_file, STDIN_FILENO);
	dup2(write_pipe, STDOUT_FILENO);
	close(write_pipe);
	close(read_pipe);
	if (command->cmd == NULL)
		handle_error(CMD_NOT_FOUND);
	else if (execve(command->cmd, command->argv, command->envp) == -1)
		handle_error(CMD_NOT_FOUND);
}

void	intermediate_process(t_pipex *pipex, t_cmd *command)
{
	short	read_pipe;
	short	write_pipe;


	read_pipe = pipex->fd_pipe[0];
	write_pipe = pipex->fd_pipe[1];

	ft_printf("pipe fd[0]: %d\n", read_pipe);
	ft_printf("pipe fd[1]: %d\n", write_pipe);
	
	dup2(read_pipe, STDIN_FILENO);
	dup2(write_pipe, STDOUT_FILENO);
	close(write_pipe);
	close(read_pipe);
	if (command->cmd == NULL)
		handle_error(CMD_NOT_FOUND);
	else if (execve(command->cmd, command->argv, command->envp) == -1)
		handle_error(CMD_NOT_FOUND);
}

void	final_process(t_pipex *pipex, t_cmd *command)
{
	short	read_pipe;
	short	write_pipe;


	read_pipe = pipex->fd_pipe[0];
	write_pipe = pipex->fd_pipe[1];
	
	ft_printf("pipe fd[0]: %d\n", read_pipe);
	ft_printf("pipe fd[1]: %d\n", write_pipe);
	
	dup2(pipex->fd_output_file, STDOUT_FILENO);
	dup2(read_pipe, STDIN_FILENO);
	close(write_pipe);
	close(read_pipe);
	if (command->cmd == NULL)
		handle_error(CMD_NOT_FOUND);
	else if (execve(command->cmd, command->argv, command->envp) == -1)
		handle_error(CMD_NOT_FOUND);
}
