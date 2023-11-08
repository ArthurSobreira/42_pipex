/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:01:30 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/08 10:47:41 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

# define ANY_CHILD -1

typedef enum e_pros
{
	INITIAL,
	FINAL,
}		t_pros;

typedef struct s_cmd
{
	pid_t	pid;
	t_pros	pros;
	char	*cmd;
	char	**argv;
	char	**envp;
}			t_cmd;

typedef struct s_pipex
{
	int		fd_input_file;
	int		fd_output_file;
	int		fd_pipe[2];
	size_t	commands;
	t_cmd	*commands_array;
}			t_pipex;

void	start_io_files(t_pipex *pipex, char *argv[]);
void	start_input_file(t_pipex *pipex, char *in_file);
void	start_output_file(t_pipex *pipex, char *out_file);

void	execute_commands(t_pipex *pipex);
void	exec_child_process(t_pipex *pipex, t_cmd *command);

void	handle_error(short exit_code);
void	handle_file_error(short exit_code, char *file_name);
void	close_all(t_pipex *pipex, short exit_code);

#endif