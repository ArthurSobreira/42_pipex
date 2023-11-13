/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:28:20 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/13 12:31:07 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	clear_all(t_pipex *pipex, short exit_code)
{
	close(STDIN_FILENO);
	close(pipex->fd_input_file);
	close(pipex->fd_output_file);
	free(pipex->commands_array);
	if ((pipex->success == TRUE) && (exit_code == 0))
		handle_error(0);
	else
		handle_error(exit_code);
}

void	clear_invalid_command(t_pipex *pipex, size_t cmd_pos)
{
	while (cmd_pos < pipex->commands)
	{
		free(pipex->commands_array[cmd_pos].cmd);
		if (pipex->commands_array[cmd_pos].argv)
			free_split(pipex->commands_array[cmd_pos].argv);
		cmd_pos++;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	clear_all(pipex, CMD_NOT_FOUND);
}

void	free_split(char **split)
{
	size_t	index;

	index = 0;
	while (split[index] != NULL)
	{
		free(split[index]);
		index++;
	}
	free(split);
}

void	free_variables(char *var, char **split_var)
{
	if (var != NULL)
		free(var);
	if (split_var != NULL)
		free_split(split_var);
}
