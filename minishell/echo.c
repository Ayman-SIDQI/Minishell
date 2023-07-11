/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:20:46 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/12 12:22:24 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *flag)
{
	int	i;

	i = 1;
	if (!flag)
		return (1);
	if (flag[0] != '-')
		return (1);
	if (flag[1] != 'n')
		return (1);
	while (flag[i] == 'n')
		i++;
	if (flag[i] == '\0')
		return (0);
	return (1);
}

int	check_start_echo(char **args)
{
	int	i;

	i = 1;
	while (!check_flag(args[i]))
		i++;
	if (args[i] == NULL)
		return (0);
	return (i);
}

void	echo(t_redir *redirs)
{
	int	n;
	int	i;

	n = 1;
	if (!redirs->refined_cmd[1])
	{
		printf("\n");
		return ;
	}
	if (!check_flag(redirs->refined_cmd[1]))
		n = 0;
	i = check_start_echo(redirs->refined_cmd);
	if (i == 0)
		return ;
	while (redirs->refined_cmd[i])
	{
		printf("%s", redirs->refined_cmd[i]);
		if (redirs->refined_cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == 1)
		printf("\n");
	g_struct->ex_st = 0;
}
