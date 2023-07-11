/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:34:06 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:31:48 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*info_dump(t_stack *tokens, t_redir *list)
{
	t_stack	*tmp;
	int		file_count;
	int		her_fd_count;

	file_count = 0;
	her_fd_count = 0;
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == LISR || tmp->type == LIMN \
		|| tmp->type == APPEND)
			file_count++;
		if (tmp->type == HER_ARG)
		{
			her_fd_count++;
			file_count++;
		}
		tmp = tmp->next;
	}
	fill_list_infdump(list, tokens, file_count, her_fd_count);
	list->file_name[file_count] = NULL;
	list = set_dir_type(tokens, list);
	return (list);
}

void	in_out_dup(t_redir *redirs)
{
	int	i;

	i = 0;
	while (redirs->file_name[i])
	{
		if (redirs->type[i] == IN_FILE || redirs->type[i] == HER_ARG)
			set_input(redirs, i);
		else if (redirs->type[i] == OUT_FILE || redirs->type[i] == APPEND)
			set_output(redirs, i);
		i++;
	}
}

void	arch_exec(t_stack *tokens)
{
	t_stack	*tmp;
	t_redir	*redirs;
	t_redir	*r_head;
	int		i;

	i = 0;
	redirs = NULL;
	tmp = tokens;
	redirs = creat_cmdlist(pipe_counter(tokens));
	r_head = redirs;
	while (tmp)
	{
		if (check_pipe(tmp) == 0)
			break ;
		redirs = info_dump(tmp, redirs);
		while (tmp && (tmp->type != PIPE))
		{
			tmp = tmp->next;
		}
		redirs = redirs->next;
		tmp = tmp->next;
	}
	redirs = info_dump(tmp, redirs);
	absocute(r_head, tokens);
}
