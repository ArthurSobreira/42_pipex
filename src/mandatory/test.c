/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:58:26 by arsobrei          #+#    #+#             */
/*   Updated: 2023/10/26 15:45:52 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	test_execve(void)
{
	char	*argv[] = {"ls", "-lha", NULL};
	char	*path;
	pid_t	child_pid;

	path = "/bin/ls";
	
	child_pid = fork(); // for the child process, pid == 0
	if (child_pid == 0)
	{
		if (execve(path, argv, NULL) < 0)
			ft_printf("Unable to run '%s'\n", path);
		exit(0);
	}
	ft_printf("\n");
	return (child_pid);
}

static int	test_execve_script(void)
{
	char	*argv[] = {"/bin/bash", "script.sh", NULL};
	char	*path;
	pid_t	child_pid;

	path = "/bin/bash";

	child_pid = fork(); // for the child process, pid == 0
	if (child_pid == 0)
	{
		if (execve(path, argv, NULL) < 0)
			ft_printf("Unable to run '%s'\n", path);
		exit(0);
	}
	ft_printf("\n");
	return (child_pid);
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
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("main PID: %d\n", pid);
	
	// Run 'chmod xxx script.sh && ls -la script.sh && ./pipex'
	test_access();

	test_execve();
	wait(NULL);
    
	test_execve_script();
	wait(NULL);

	ft_printf("final PID: %d\n", pid);
	return (0);
}
