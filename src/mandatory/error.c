/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:37 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/07 11:48:44 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(short exit_code)
{
	if (exit_code == 0)
		ft_printf("\033[32;3mPipex executed successfully :)\033[0m\n");
	if (exit_code == 1)
		ft_printf("\033[31;3mError, invalid parameter usage :(\033[0m\n");
	if (exit_code == 2)
		ft_printf("\033[31;3mError, cannot initialize pipe :(\033[0m\n");
	if (exit_code == 3)
		ft_printf("\033[31;3mError, cannot initialize fork :(\033[0m\n");
	if (exit_code == 4)
		ft_printf("\033[31;3mError, cannot initialize commands :(\033[0m\n");
	exit(exit_code);
}

void	handle_file_error(short exit_code, char *file_name)
{
	if (exit_code == 1)
		ft_printf("\033[31;3mError, '%s' file not found :(\033[0m\n", file_name);
	if (exit_code == 2)
		ft_printf("\033[31;3mError, cannot read file '%s' :(\033[0m\n", file_name);
	if (exit_code == 3)
		ft_printf("\033[31;3mError, cannot open file '%s' :(\033[0m\n", file_name);
	exit(exit_code);
}
