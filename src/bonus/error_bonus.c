/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:37 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/12 12:41:47 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	handle_error(short exit_code)
{
	if (exit_code == 0)
		ft_printf("\033[32;3mPipex executed successfully :)\033[0m\n");
	if (exit_code == CMD_NOT_FOUND)
		perror("\033[31;3mError, command not found :(\033[0m\n");
	if (exit_code == 1)
		perror("\033[31;3mError, invalid parameter usage :(\033[0m\n");
	if (exit_code == 2)
		perror("\033[31;3mError, cannot initialize pipe :(\033[0m\n");
	if (exit_code == 3)
		perror("\033[31;3mError, cannot initialize fork :(\033[0m\n");
	if (exit_code == 4)
		perror("\033[31;3mError, cannot initialize commands :(\033[0m\n");
	if (exit_code == 5)
		perror("\033[31;3mError, invalid here_doc usage :(\033[0m\n");
	exit(exit_code);
}

void	handle_file_error(short exit_code)
{
	if (exit_code == 1)
		perror("\033[31;3mError, file not found :(\033[0m\n");
	if (exit_code == 2)
		perror("\033[31;3mError, cannot read file :(\033[0m\n");
	if (exit_code == 3)
		perror("\033[31;3mError, cannot open file :(\033[0m\n");
	exit(exit_code);
}
