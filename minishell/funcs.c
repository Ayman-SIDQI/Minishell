/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:23:14 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:07:59 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_tolist(t_stack **tokens, char *str, char **amal)
{
	ft_lstadd_back(tokens, ft_lstnew(str, NONE));
	*amal[0] = '\0';
}

void	let_split(char **doubl, char *s, char **amal, t_stack **tokens)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	if (s[0] != ' ' && s[0])
	{
		*amal = ft_strjoin2(*amal, doubl[i]);
		i++;
	}
	if (doublelengh(doubl) > 1 || s[ft_strlen(s) - 1] == ' ')
		ft_add_tolist(tokens, *amal, amal);
	else
		return ;
	while (i < doublelengh(doubl) - 1)
	{
		ft_add_tolist(tokens, doubl[i], amal);
		i++;
	}
	if (s[ft_strlen(s) - 1] != ' ' && doublelengh(doubl) > 1)
		*amal = ft_strjoin2(*amal, doubl[i]);
	else if (s[ft_strlen(s) - 1] == ' ')
		ft_add_tolist(tokens, doubl[i], amal);
}

void	set_ewt_values(int *found, t_stack **temp, char **s)
{
	*found = 0;
	*temp = g_struct->env_list;
	*s = NULL;
}

int	ewt_checker(char *line, int *i, char **amal)
{
	if (ft_strlen2(&line[*i + 1]) == 0)
	{
		*amal = ft_strjoin(*amal, line[*i]);
		*i += ft_strlen2(&line[*i + 1]) + 1;
		return (1);
	}
	return (0);
}

void	expandwithtokens(char **amal, int *i, char *line, t_stack **tokens)
{
	t_stack	*temp;
	int		found;
	char	*s;
	char	**doubl;

	set_ewt_values(&found, &temp, &s);
	if (ewt_checker(line, i, amal))
		return ;
	while (temp)
	{
		if (!comparethething(&line[*i + 1], temp->content))
		{
			shrink_exptokens(&found, &s, temp);
			doubl = ft_split(s, ' ');
			if (doubl[0] != NULL)
				let_split(doubl, s, amal, tokens);
			free_2d(doubl);
			*i += ft_strlen2(&line[*i + 1]) + 1;
			break ;
		}
		temp = temp->next;
	}
	if (!found || !s)
		*i += ft_strlen2(&line[*i + 1]) + 1;
	free (s);
}
