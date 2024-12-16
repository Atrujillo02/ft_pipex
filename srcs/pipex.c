/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:34:53 by atrujill          #+#    #+#             */
/*   Updated: 2022/11/07 10:38:06 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child1_process(int *fd_file, int *fd, char **argv, char **envp)
{
	char	**cmd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_failure("Fork");
	if (pid == 0)
	{
		fd_file[0] = open(argv[1], O_RDONLY);
		if (fd_file[0] < 0)
			ft_failure(argv[1]);
		close(fd[FILE_IN]);
		dup2(fd_file[0], STDIN_FILENO);
		dup2(fd[FILE_OUT], STDOUT_FILENO);
		cmd = ft_split(argv[2], ' ');
		if (cmd[0] && ft_get_path(cmd[0], envp))
		{
			execve(ft_get_path(cmd[0], envp), cmd, envp);
			ft_free_paths(cmd);
		}
		else
			ft_error_cmd(cmd);
	}
}

void	child2_process(int *fd_file, int *fd, char **argv, char **envp)
{
	char	**cmd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_failure("Fork");
	if (pid == 0)
	{
		fd_file[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_file[1] < 0)
			ft_failure(argv[4]);
		close(fd[FILE_OUT]);
		dup2(fd[FILE_IN], STDIN_FILENO);
		dup2(fd_file[1], STDOUT_FILENO);
		cmd = ft_split(argv[3], ' ');
		if (cmd[0] && ft_get_path(cmd[0], envp))
		{
			execve(ft_get_path(cmd[0], envp), cmd, envp);
			ft_free_paths(cmd);
		}
		else
			ft_error_cmd(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd_file[2];
	int	fd[2];
	
	errno= 0;
	if (argc == 5)
	{
		pipe(fd);
		if (pipe(fd) < 0)
			ft_failure(NULL);
		child1_process(fd_file, fd, argv, envp);
		child2_process(fd_file, fd, argv, envp);
		close(fd[FILE_IN]);
		close(fd[FILE_OUT]);
		waitpid(-1, NULL, 0);
		waitpid(-1, NULL, 0);
	}
	else
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
