/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:33:22 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/12 16:05:43 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

# define CMD_NOT_FOUND 127
# define SPACE 32
# define TWO_POINTS 58

typedef enum e_proc
{
	INITIAL,
	INTERMEDIATE,
	FINAL,
}		t_proc;

typedef enum e_bool
{
	FALSE,
	TRUE,
}		t_bool;

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
	char	*limiter;
	size_t	commands;
	size_t	cmd_index;
	t_cmd	*commands_array;
	t_bool	has_heredoc;
	t_bool	success;
}			t_pipex;

void	start_io_files(t_pipex *pipex, char *argv[]);
void	start_input_file(t_pipex *pipex, char *in_file);
void	start_output_file(t_pipex *pipex, char *out_file);
void	here_doc(t_pipex *pipex);

void	get_commands(t_pipex *pipex, char *argv[], char *envp[]);
char	*validate_path(char *cmd_name, char **split_path);
char	*get_cmd_path(char *cmd_name, char *envp[]);
char	*get_cmd_name(char *cmd_name);
char	**get_arguments(char *argv);

void	execute_commands(t_pipex *pipex);
void	exec_child_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos);
void	initial_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos);
void	intermediate_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos);
void	final_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos);

void	handle_error(short exit_code);
void	handle_file_error(short exit_code);
void	clear_all(t_pipex *pipex, short exit_code);
void	clear_invalid_command(t_pipex *pipex, size_t cmd_pos);
void	free_split(char **split);
void	free_variables(char *var, char **split_var);


#endif