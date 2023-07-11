/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:16:12 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/16 21:42:56 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

short	check_builtins(char	**refined_cmd)
{
	if (!(ft_strcmp(refined_cmd[0], "pwd")) \
		|| !(ft_strcmp(refined_cmd[0], "cd")) \
		|| !(ft_strcmp(refined_cmd[0], "echo")) \
		|| !(ft_strcmp(refined_cmd[0], "exit")) \
		|| !(ft_strcmp(refined_cmd[0], "unset")) \
		|| !(ft_strcmp(refined_cmd[0], "env")) \
		|| !(ft_strcmp(refined_cmd[0], "export")))
		return (1);
	return (0);
}

char	**sgl_refine(t_stack *tokens, int i)
{
	t_stack	*tmp;
	char	**refined_cmd;

	tmp = tokens;
	while (tmp && (tmp->type != PIPE))
	{
		if (tmp->type == CMD || tmp->type == ARG)
			i++;
		tmp = tmp->next;
	}
	refined_cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!refined_cmd)
		return (NULL);
	tmp = tokens;
	fill_refined(&tmp, refined_cmd);
	refined_cmd[i] = NULL;
	return (refined_cmd);
}
