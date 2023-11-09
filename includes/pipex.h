/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:01:30 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/09 16:46:26 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

# define ANY_CHILD -1
# define SPACE 32
# define TWO_POINTS 58
# define CMD_NOT_FOUND 127

typedef enum e_proc
{
	INITIAL,
	FINAL,
}		t_proc;

typedef struct s_cmd
{
	pid_t	pid;
	t_proc	proc_type;
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

void	get_commands(t_pipex *pipex, char *argv[], char *envp[]);
char	*get_cmd_path(char *cmd_name, char *envp[]);
char	*get_cmd_name(char *cmd_name);
char	**get_arguments(char *argv);

void	execute_commands(t_pipex *pipex);
void	exec_child_process(t_pipex *pipex, t_cmd *command);

void	handle_error(short exit_code);
void	handle_file_error(short exit_code);
void	clear_all(t_pipex *pipex, short exit_code);
void	free_split(char **split);

#endif