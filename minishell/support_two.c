/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:13:11 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 10:43:32 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rmexplist(char **args)
{
	int		i;
	char	*s;

	i = -1;
	while (args[++i])
	{
		if (checkexarg(args[i]))
		{
			s = thebefeq(args[i]);
			deletenode(&g_struct->env_list, s);
			free (s);
		}
		else
		{
			printf ("unset: not an identifier: %s\n", args[i]);
			g_struct->ex_st = 1;
		}
	}
}

void	printexport(void)
{
	t_stack	*temp;
	int		i;

	temp = g_struct->env_list;
	while (temp)
	{
		i = -1;
		ft_putstr_fd ("declare -x ", 1);
		while (temp->content[++i] != '=' && temp->content[i])
			write(1, &temp->content[i], 1);
		if (!temp->content[i])
		{
			temp = temp->next;
			ft_putstr_fd("\n", 1);
			continue ;
		}
		ft_putstr_fd("=\"", 1);
		while (temp->content[++i])
			write(1, &temp->content[i], 1);
		ft_putstr_fd("\"\n", 1);
		temp = temp->next;
	}
}

void	export(char **args)
{
	if (!args)
		return ;
	if (args[0] == NULL)
	{
		printexport();
		return ;
	}
	addexplist(args);
}

void	unset(char **args)
{
	if (!args)
		return ;
	if (args[0] == NULL)
		return ;
	rmexplist(args);
}

void	addexplist(char **args)
{
	int		error;
	int		i;
	char	*s;

	i = -1;
	error = 0;
	while (args[++i])
	{
		if (checkexarg(args[i]))
		{
			s = thebefeq(args[i]);
			deletenode(&g_struct->env_list, s);
			ft_lstadd_back(&g_struct->env_list, ft_lstnew(args[i], NONE));
			free (s);
		}
		else
		{
			if (error == 1)
				continue ;
			printf ("export: not an identifier: %s\n", args[i]);
			error = 1;
		}
	}
	if (error == 1)
		g_struct->ex_st = 1;
}
