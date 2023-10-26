/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:58:26 by arsobrei          #+#    #+#             */
/*   Updated: 2023/10/26 10:40:35 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	test_execve(void)
{
	char	*argv[] = {"ls", "-lha", NULL};
	char	*path;

	path = "/bin/ls";
	if (execve(path, argv, NULL) < 0)
		ft_printf("Unable to run '%s'\n", path);
	ft_printf("\n");
}

static void	test_execve_script(void)
{
	char	*argv[] = {"/bin/bash", "script.sh", NULL};
	char	*path;

	path = "/bin/bash";
	if (execve(path, argv, NULL) < 0)
		ft_printf("Unable to run '%s'\n", path);
	ft_printf("\n");
}

static void	test_access(void)
{
	const char	*file_name;

	file_name = "script.sh";
	if (access(file_name, F_OK) == 0)
		ft_printf("The file %s exist\n", file_name);
	if (access(file_name, R_OK) == 0)
		ft_printf("The file %s is readable\n", file_name);
	if (access(file_name, W_OK) == 0)
		ft_printf("The file %s is writable\n", file_name);
	if (access(file_name, X_OK) == 0)
		ft_printf("The file %s is executable\n", file_name);
	ft_printf("\n");
}

int	main(void)
{
	// Run 'chmod xxx script.sh && ls -la script.sh && ./pipex'
	test_access();
	
	test_execve();
	test_execve_script();
	return (0);
}
