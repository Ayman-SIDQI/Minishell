/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:32:44 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:31:58 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char *cmd_token)
{
	int		i;
	char	*full_path;

	i = 0;
	while (g_struct->split_paths[i])
	{
		if (!(ft_strchr(cmd_token, '/')))
		{
			full_path = ft_strjoin2(g_struct->split_paths[i], "/");
			full_path = ft_strjoin2(full_path, cmd_token);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
		}
		else
		{
			if (access(cmd_token, X_OK) == 0)
				return (cmd_token);
		}
		i++;
	}
	return (NULL);
}

int	check_pipe(t_stack *cmds)
{
	t_stack	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	set_input(t_redir *redirs, int i)
{
	int	fd;

	if (redirs->type[i] == IN_FILE)
	{
		fd = open(redirs->file_name[i], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("Shellito:", 2);
			perror(redirs->file_name[i]);
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	else if (redirs->type[i] == HER_ARG)
	{
		dup2(redirs->read_her, 0);
		close(redirs->read_her);
	}
}

void	set_output(t_redir *redirs, int i)
{
	int	fd;

	fd = 0;
	if (redirs->type[i] == APPEND)
		fd = open(redirs->file_name[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (redirs->type[i] == OUT_FILE)
		fd = open(redirs->file_name[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redirs->file_name[i]);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}
