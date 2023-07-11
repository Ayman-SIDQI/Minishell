/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:30:16 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:34:41 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	limn_setter(t_stack	**temp, t_redir	**list, int i)
{
	if ((*temp)->next)
		(*list)->file_name[i] = ft_strdup((*temp)->next->content);
	if ((*temp)->type == LIMN)
		(*list)->type[i] = OUT_FILE;
	else
		(*list)->type[i] = APPEND;
}

int	lisr_setter(t_stack	**temp, t_redir	**list, int i, int h_c)
{
	if ((*temp)->next)
		(*list)->file_name[i] = ft_strdup((*temp)->next->content);
	(*list)->type[i] = IN_FILE;
	if ((*temp)->type == HEREDOC)
	{
		h_c++;
		(*list)->type[i] = HER_ARG;
	}
	return (h_c);
}

t_redir	*set_dir_type(t_stack *tokens, t_redir	*list)
{
	t_stack	*temp;
	int		i;
	int		heredoc_count;

	temp = tokens;
	i = 0;
	heredoc_count = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == LIMN || temp->type == APPEND)
		{
			limn_setter(&temp, &list, i);
			i++;
		}
		else if (temp->type == HEREDOC || temp->type == LISR)
		{
			heredoc_count = lisr_setter(&temp, &list, i, heredoc_count);
			i++;
		}
		temp = temp->next;
	}
	list->heredoc_num = heredoc_count;
	return (list);
}

int	valid_dir(char **directory)
{
	int	i;
	DIR	*dir_struct;

	i = 0;
	if (!*directory)
		return (1);
	while (directory[i])
	{
		dir_struct = opendir(directory[i]);
		if (dir_struct != NULL)
			closedir(dir_struct);
		else
			return (1);
		i++;
	}
	return (0);
}
