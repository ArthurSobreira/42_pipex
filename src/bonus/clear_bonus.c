/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:28:20 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/10 12:14:56 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	clear_all(t_pipex *pipex, short exit_code)
{
	close(pipex->fd_input_file);
	close(pipex->fd_output_file);
	free(pipex->commands_array);
	if ((pipex->success == TRUE) && (exit_code == 0))
		handle_error(0);
	else
		handle_error(exit_code);
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
