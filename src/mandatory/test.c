/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:58:26 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/06 10:19:06 by arsobrei         ###   ########.fr       */
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

static void	test_dup2(void)
{
	int		fd;
	int		fd2;
	char	line[7];
	char	line2[5];
	int		bytes_read;

	fd = open("Makefile", O_RDONLY);
	bytes_read = read(fd, line, 7);
	line[bytes_read] = '\0';
	ft_printf("fd%d line: %s\n", fd, line);

	fd2 = dup2(fd, 5);
	bytes_read = read(fd2, line2, 5);
	line2[bytes_read] = '\0';
	ft_printf("fd%d line: %s\n\n", fd2, line2);
	
	close(fd);
	close(fd2);
}

static void	test_pipe(void)
{
	char	*msg1 = "Hello, World 01";
	char	*msg2 = "Hello, World 02";
	char	*msg3 = "Hello, World 03\n";
	int		msg_size = 16;
	char	buffer[msg_size];
	int		fd[2];
	
	if (pipe(fd) >= 0)
	{
		write(fd[1], msg1, msg_size);
		write(fd[1], msg2, msg_size);
		write(fd[1], msg3, msg_size);

		for (int i = 0; i < 3; i++)
		{
			read(fd[0], buffer, msg_size);
			ft_printf("%s\n", buffer);
		}
		close(fd[0]);
		close(fd[1]);
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("main PID: %d\n", pid);
	
	// Run 'chmod xxx script.sh && ls -la script.sh && ./pipex'
	test_access();

	// Execve tests
	test_execve();
	wait(NULL);
	test_execve_script();
	wait(NULL);
	
	// Dup2 tests
	test_dup2();

	// Pipe tests
	test_pipe();

	ft_printf("final PID: %d\n", pid);
	return (0);
}
