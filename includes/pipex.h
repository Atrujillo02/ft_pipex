/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:44:55 by atrujill          #+#    #+#             */
/*   Updated: 2022/11/07 11:11:06 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

# define FILE_IN 0
# define FILE_OUT 1

/*Pipex*/

void	child1_process(int *fd_file, int *fd, char **argv, char **envp);
void	child2_process(int *fd_file, int *fd, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);

/*Utils_pipex*/
void	ft_failure(char *text);
void	ft_error_cmd(char **cmd);
void	ft_free_paths(char **paths);
char	**ft_all_the_paths(char **envp);
char	*ft_get_path(char *cmd, char **envp);
#endif
