/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:36:57 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:20:34 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	envp_to_linked_list(char **array)
{
	t_stack	*new_node;
	int		i;

	i = 0;
	new_node = NULL;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		new_node = ft_lstnew(array[i], 0);
		if (new_node)
			ft_lstadd_back(&g_struct->env_list, new_node);
		i++;
	}
}

char	*var_extract(char *line)
{
	int		i;
	char	*extracted;

	i = 0;
	if ((!ft_isalpha(line[i]) && line[i] != '_') || !line[0])
		return (NULL);
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	extracted = ft_substr(line, 0, i);
	return (extracted);
}

void	expandstatus(char **amal, int *i)
{
	char	*s;

	s = ft_itoa(g_struct->ex_st);
	*amal = ft_strjoin2(*amal, s);
	*i += 2;
	free(s);
}

int	comparethething(char *s1, char *s2)
{
	char	*extracted;
	char	*env_name;
	int		i;

	extracted = var_extract(s1);
	env_name = envp_name(s2);
	i = ft_strcmp2(extracted, env_name);
	free (extracted);
	free (env_name);
	return (i);
}

void	exp_normal_exp(t_stack *temp, char **amal, int *found)
{
	char	*envs;

	envs = envp_value(temp->content);
	*amal = ft_strjoin2 (*amal, envs);
	free (envs);
	*found = 1;
}
