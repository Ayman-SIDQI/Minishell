/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absocute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:08:21 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 10:42:37 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_exit(int n_exit, t_redir *redirs, t_stack *tokens, short mode)
{
	(void)tokens;
	if (mode == 0)
	{
		ft_putstr_fd("Shellito:", 2);
		ft_putstr_fd(redirs->refined_cmd[0], 2);
		ft_putstr_fd(" command not found\n", 2);
		exit(n_exit);
	}
	else if (mode == 1)
	{
		ft_putstr_fd("Shellito:", 2);
		ft_putstr_fd(redirs->refined_cmd[0], 2);
		ft_putstr_fd(" is a directory\n", 2);
		exit(n_exit);
	}
}

void	freet_redir(t_redir **redirs)
{
	t_redir	*tmp;

	tmp = (*redirs);
	while (*redirs)
	{
		tmp = *redirs;
		free_2d((*redirs)->refined_cmd);
		free_2d((*redirs)->file_name);
		free((*redirs)->type);
		*redirs = (*redirs)->next;
		free(tmp);
	}
}

void	freet_stack(t_stack **tokens)
{
	t_stack	*tmp;

	tmp = (*tokens);
	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->content);
		free(tmp);
	}
}

void	absocute(t_redir *redirs, t_stack *tokens)
{
	int		pipe_x[2];
	int		pipe_y[2];
	int		*pid_arr;
	t_redir	*redirs2;
	size_t	i;

	i = -1;
	redirs2 = redirs;
	pid_arr = (int *)malloc(sizeof(int) * (pipe_counter(tokens) + 1));
	if (!pid_arr)
		return ;
	pid_arr[pipe_counter(tokens)] = 0;
	if (pipe(pipe_x) == -1 || pipe(pipe_y) == -1)
		return ;
	heredoc(redirs);
	while (++i <= pipe_counter(tokens))
	{
		pid_arr[i] = fork();
		if (pid_arr[i] == 0)
		{
			pipe_sys(i, pipe_x, pipe_y, pipe_counter(tokens));
			in_out_dup(redirs);
			error_func(redirs, tokens);
			isdir_ismultiple(redirs, tokens);
		}
		reopening(i, pipe_x, pipe_y);
		redirs = redirs->next;
	}
	free_absocute(&redirs2, &tokens, pipe_x, pipe_y);
	process_monitor(pid_arr, pipe_counter(tokens));
}
