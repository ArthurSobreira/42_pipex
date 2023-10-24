/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:58:26 by arsobrei          #+#    #+#             */
/*   Updated: 2023/10/24 20:03:37 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	test_access(void)
{
	const char	*file_name;

	file_name = "test.txt";
	if (access(file_name, F_OK) == 0)
		printf("The file %s exist\n", file_name);
	if (access(file_name, R_OK) == 0)
		printf("The file %s is readable\n", file_name);
	if (access(file_name, W_OK) == 0)
		printf("The file %s is writable\n", file_name);
	if (access(file_name, X_OK) == 0)
		printf("The file %s is executable\n", file_name);
}

int	main(void)
{
	// Run 'chmod xxx test.txt && ls -la test.txt && ./pipex'
	test_access();
	return (0);
}
