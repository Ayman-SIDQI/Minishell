/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharia < hcharia@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:35:21 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/12 15:09:29 by hcharia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envp_name(char *full_line)
{
	int		i;
	char	*extracted;

	i = 0;
	while (full_line[i] != '=' && full_line[i] != '\0')
		i++;
	extracted = ft_substr(full_line, 0, i);
	return (extracted);
}

char	*envp_value(char *full_line)
{
	int		i;
	int		len;
	int		start_point;
	char	*extracted;

	i = 0;
	len = 0;
	while (full_line[i] != '=' && full_line[i] != '\0')
		i++;
	i++;
	if (full_line[i] == '\0')
		return (NULL);
	start_point = i;
	while (full_line[i] != '\0')
	{
		i++;
		len++;
	}
	extracted = ft_substr(full_line, start_point, len);
	return (extracted);
}

int	cdto_home(void)
{
	char	*home;
	t_stack	*temp;

	temp = g_struct->env_list;
	while (temp)
	{
		if (!comparethething("HOME", temp->content))
		{
			home = envp_value(temp->content);
			chdir(home);
			free(home);
			return (1);
		}
	temp = temp->next;
	}
	return (0);
}

void	cd(t_redir *redirs)
{
	if (!redirs->refined_cmd[1])
	{
		if (cdto_home())
			return ;
	}
	if (!redirs->refined_cmd[1])
	{
		printf ("cd: HOME not set\n");
		g_struct->ex_st = 1;
		return ;
	}
	if (chdir(redirs->refined_cmd[1]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", \
		redirs->refined_cmd[1]);
		g_struct->ex_st = 1;
	}
}
