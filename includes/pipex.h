/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsobrei <arsobrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:01:30 by arsobrei          #+#    #+#             */
/*   Updated: 2023/11/06 11:56:29 by arsobrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd_input_file;
	int		fd_output_file;
	int		fd_pipe[2];
}			t_pipex;

typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
	char	**envp;
}			t_cmd;

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

void	start_io_files(t_pipex *pipex, char *argv[]);
void	start_input_file(t_pipex *pipex, char *in_file);
void	start_output_file(t_pipex *pipex, char *out_file);

void	handle_error(short exit_code);
void	handle_file_error(short exit_code, char *file_name);

#endif