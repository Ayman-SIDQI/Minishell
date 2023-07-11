/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:27:24 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:10:44 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	fill_list_infdump(t_redir *list, t_stack *tokens, int fc, int h_f_c)
{
	list->refined_cmd = refine(tokens);
	list->file_name = (char **)malloc (sizeof(char *) * (fc + h_f_c + 1));
	list->type = (int *)malloc (sizeof (int) * (fc + h_f_c + 1));
	list->type[fc + h_f_c] = 69;
	if (!list->file_name || !list->type)
		exit (1);
}

t_redir	*sgl_info_dump(t_stack *tokens, t_redir *list)
{
	int		i;
	t_stack	*tmp;
	int		file_count;
	int		her_fd_count;

	i = 0;
	file_count = 0;
	her_fd_count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == LISR || tmp->type == LIMN || tmp->type == APPEND)
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

void	close_fds(void)
{
	close (0);
	close (1);
	dup2(g_struct->std_in, 0);
	dup2(g_struct->std_out, 1);
}

short	single(t_stack *tokens)
{
	t_redir	*redirs;
	char	**refined_cmd;

	redirs = NULL;
	refined_cmd = NULL;
	if (pipe_counter(tokens) == 0)
	{
		refined_cmd = sgl_refine(tokens, 0);
		if (check_builtins(refined_cmd))
		{
			redirs = creat_cmdlist(0);
			redirs = sgl_info_dump(tokens, redirs);
			heredoc(redirs);
			in_out_dup(redirs);
			builtin_exec(redirs, 69);
			close_fds();
			free_2d(refined_cmd);
			freet_redir(&redirs);
			freet_stack(&tokens);
			return (1);
		}
		free_2d(refined_cmd);
	}
	return (0);
}

short	multiple( t_redir	*redirs)
{
	if (check_builtins(redirs->refined_cmd))
	{
		builtin_exec(redirs, -1);
		exit(g_struct->ex_st);
		return (0);
	}
	return (1);
}
