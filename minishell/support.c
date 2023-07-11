/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:02:37 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:11:39 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shrink_exptokens(int *found, char **s, t_stack *temp)
{
	char	*env;

	*found = 1;
	env = envp_value(temp->content);
	*s = ft_strdup(env);
	free(env);
}

void	removequotes(t_stack *temp, char **s)
{
	int	i;

	i = 0;
	while (temp->content[i] && chfh2(temp))
	{
		if (temp->content[i] == '"')
			set_double2(s, &i, temp->content);
		else if (temp->content[i] == '\'')
			set_single2(s, &i, temp->content);
		else
			*s = ft_strjoin(*s, temp->content[i]);
		i++;
	}
}

int	parsing(t_stack **tokens)
{
	t_stack	*temp;
	char	*s;

	temp = *tokens;
	if (!piping_err(temp) || !redirection_err(temp))
	{
		freet_stack(tokens);
		return (0);
	}
	set_type(*tokens);
	while ((temp))
	{
		s = malloc(1);
		s[0] = '\0';
		removequotes(temp, &s);
		free (temp->content);
		if (!chfh2(temp))
			s = ft_strdup(temp->content);
		temp->content = s;
		temp = temp->next;
	}
	return (1);
}

void	env(void)
{
	t_stack	*temp;

	temp = g_struct->env_list;
	while (temp)
	{
		if (checkequal(temp->content))
			printf("%s\n", temp->content);
		temp = temp->next;
	}
}
