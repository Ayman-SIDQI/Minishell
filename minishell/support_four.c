/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:29:30 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:38:18 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	search_linkedl(void)
{
	t_stack	*tmp;
	char	*str;
	char	*str2;

	tmp = g_struct->env_list;
	while (tmp)
	{
		str = envp_name(tmp->content);
		if (ft_strcmp(str, "PATH") == 0)
		{
			free(str);
			str2 = envp_value(tmp->content);
			g_struct->split_paths = ft_split(str2, ':');
			free(str2);
			if (g_struct->split_paths == NULL)
				return (0);
			return (1);
		}
		free(str);
		tmp = tmp->next;
	}
	return (0);
}

void	execv_func(t_redir *r, t_stack *tokens)
{
	if (execve(r->refined_cmd[0], r->refined_cmd, g_struct->envp) == -1)
	{
		if (r->heredoc_num == 0 && !r->refined_cmd[0])
			ft_putstr_fd("SSShellito: Command not found\n", 2);
		freet_stack(&tokens);
		freet_redir(&r);
		exit(2);
	}
}

void	cmd_notfound(t_redir **redirs, t_stack **tokens, char *cmd)
{
	ft_putstr_fd("Shellito: Command not found\n", 2);
	freet_stack(tokens);
	freet_redir(redirs);
	free(cmd);
	exit (127);
}

void	act_execute(t_redir *redirs, t_stack *tokens)
{
	char	*cmd;

	cmd = NULL;
	if (search_linkedl())
	{
		cmd = join_path(redirs->refined_cmd[0]);
		if (cmd == NULL || cmd[0] == '\0')
			cmd_notfound(&redirs, &tokens, cmd);//needs to be tested cause im sleepy and mamsalich
		else if (execve(cmd, redirs->refined_cmd, g_struct->envp) == -1)
		{
			if (redirs->heredoc_num == 0 && !redirs->refined_cmd[0])
				ft_putstr_fd("Shellito: Command not found\n", 2);
			freet_stack(&tokens);
			freet_redir(&redirs);
			free(cmd);
			exit(2);
		}
	}
	else if (access(redirs->refined_cmd[0], F_OK) == 0)
		execv_func(redirs, tokens);
	ft_putstr_fd("Shellito: No such file or directory\n", 2);
	exit(127);
}

void	closure(int *pipe_x, int *pipe_y)
{
	close (pipe_x[0]);
	close (pipe_x[1]);
	close (pipe_y[0]);
	close (pipe_y[1]);
}
