/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:13:16 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:17:02 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	reopening(int i, int *pipe_x, int *pipe_y)
{
	if (i % 2 == 0)
	{
		close(pipe_y[0]);
		close(pipe_y[1]);
		if (pipe(pipe_y) == -1)
		{
			perror("Minishell: pipe failed");
			exit (1);
		}
	}
	else
	{
		close(pipe_x[0]);
		close(pipe_x[1]);
		if (pipe(pipe_x) == -1)
		{
			perror("Minishell: pipe failed");
			exit (1);
		}
	}
}

void	fst_cmd(int *pipe_x, int *pipe_y)
{
	close(pipe_x[0]);
	close(pipe_y[1]);
	close(pipe_y[0]);
	dup2(pipe_x[1], 1);
	close(pipe_x[1]);
}

void	mdle_cmd(int *pipe_x, int *pipe_y, int i)
{
	if (i % 2 != 0)
	{
		close (pipe_x[1]);
		close (pipe_y[0]);
		dup2(pipe_x[0], 0);
		dup2(pipe_y[1], 1);
		close(pipe_x[0]);
		close(pipe_y[1]);
	}
	else
	{
		close (pipe_y[1]);
		close (pipe_x[0]);
		dup2(pipe_y[0], 0);
		dup2(pipe_x[1], 1);
		close(pipe_y[0]);
		close(pipe_x[1]);
	}
}

void	lst_cmd(int *pipe_x, int *pipe_y, int i)
{
	if (i % 2 != 0)
	{
		close(pipe_x[1]);
		close(pipe_y[0]);
		close(pipe_y[1]);
		dup2(pipe_x[0], 0);
		close(pipe_x[0]);
	}
	else
	{
		close(pipe_y[1]);
		close(pipe_x[0]);
		close(pipe_x[1]);
		dup2(pipe_y[0], 0);
		close(pipe_y[0]);
	}
}

void	pipe_sys(size_t i, int *pipe_x, int *pipe_y, size_t pipe_num)
{
	if (pipe_num > 0)
	{
		if (i == 0)
			fst_cmd(pipe_x, pipe_y);
		else if (i > 0 && i != pipe_num)
			mdle_cmd(pipe_x, pipe_y, i);
		else
			lst_cmd(pipe_x, pipe_y, i);
	}
}
