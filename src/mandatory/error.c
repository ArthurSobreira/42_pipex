/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:37 by arsobrei          #+#    #+#             */
/*   Updated: 2023/10/26 15:38:44 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(short exit_code)
{
	if (exit_code == 0)
		ft_printf("\033[32;3mPipex executed successfully :)\033[0m\n");
	if (exit_code == 1)
		ft_printf("\033[31;3mError, invalid parameter usage :(\033[0m\n");
	exit(exit_code);
}
