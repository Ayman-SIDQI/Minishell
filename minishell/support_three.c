/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:18:34 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:52:45 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expandnormal(char **amal, int *i, char *line)
{
	t_stack	*temp;
	int		found;

	found = 0;
	temp = g_struct->env_list;
	if (ft_strlen2(&line[*i + 1]) == 0)
	{
		*amal = ft_strjoin(*amal, line[*i]);
		*i += 1;
		return ;
	}
	while (temp)
	{
		if (!comparethething(&line[*i + 1], temp->content))
		{
			exp_normal_exp(temp, amal, &found);
			*i += ft_strlen2(&line[*i + 1]) + 1;
			return ;
		}
		temp = temp->next;
	}
	if (!found)
		*i += ft_strlen2(&line[*i + 1]) + 1;
}

void	process_monitor(int *pid_arr, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		waitpid(pid_arr[i], &g_struct->status, 0);
		if (WIFSIGNALED(g_struct->status))
			g_struct->ex_st = WTERMSIG(g_struct->status) + 128;
		else if (WIFEXITED(g_struct->status))
			g_struct->ex_st = WEXITSTATUS(g_struct->status);
		i++;
	}
	free(pid_arr);
}

void	isdir_ismultiple(t_redir *redirs, t_stack *tokens)
{
	if (!valid_dir(redirs->refined_cmd))
		err_exit(127, redirs, tokens, 1);
	if (multiple(redirs))
		act_execute(redirs, tokens);
}

void	free_absocute(t_redir **redirs2, t_stack **tokens, int *p_x, int *p_y)
{
	freet_redir(redirs2);
	freet_stack(tokens);
	closure(p_x, p_y);
}

void	error_func(t_redir *redirs, t_stack *tokens)
{
	if (!*redirs->refined_cmd[0])
		err_exit(127, redirs, tokens, 0);
	if (g_struct->h_sigy)
	{
		g_struct->h_sigy = 0;
		g_struct->ex_st = 1;
		exit (1);
	}
}
