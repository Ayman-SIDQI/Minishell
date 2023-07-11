/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:29:22 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 10:50:32 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	set_s_heredoc(char **amal, char *line, int quote)
{
	int	i;

	i = -1;
	*amal = malloc (1);
	*amal[0] = '\0';
	if (!line)
		return ;
	while (line[++i] != '\0')
	{
		if (quote && line[i] == '$' && line[i + 1] != '$')
		{
			if (line[i + 1] == '?')
			{
				expandstatus(amal, &i);
				i--;
			}
			else
			{
				expandnormal (amal, &i, line);
				i--;
			}
		}
		else if (line[i] != '\0')
			*amal = ft_strjoin(*amal, line[i]);
	}
}

int	checkforquote(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

char	*rmquote(char *string)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(1);
	s[0] = '\0';
	while (string[i])
	{
		if (string[i] == '"')
			set_double2(&s, &i, string);
		else if (string[i] == '\'')
			set_single2(&s, &i, string);
		else
			s = ft_strjoin(s, string[i]);
		i++;
	}
	return (s);
}

// short	init_her(t_redir *redirs)
// {
// 	g_struct->str = NULL;
// 	pipe(g_struct->her);
// 	g_struct->o = 0;
// 	g_struct->tmp = redirs;
// 	g_struct->gib = dup(0);
// 	g_struct->content = NULL;
// 	g_struct->s = NULL;
// 	return (0);
// }

void	free_her(void)
{
	free(g_struct->str);
	free(g_struct->content);
	g_struct->content = NULL;
	free(g_struct->s);
	g_struct->s = NULL;
}

void	heredoc(t_redir *redirs)
{
	int static		i;
	char			*content;
	char			*s;
	int				her[2];
	int				o;
	t_redir			*tmp;
	char			*str;

	i = 0;
	pipe(her);
	o = 0;
	tmp = redirs;
	g_struct->gib = dup(0);
	str = NULL;
	content = NULL;
	s = NULL;
	while (tmp)
	{
		if (tmp->heredoc_num == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		g_struct->h_sigx = 1;
		while (g_struct->h_sigy == 0)
		{
			free(content);
			content = readline("heredoc > ");
			if (!content)
			{
				free(content);
				content = NULL;
				break ;
			}
			while (tmp->type && tmp->type[i] != HER_ARG && tmp->type[i] != 69)
				i++;
			set_s_heredoc(&s, content, checkforquote(tmp->file_name[i]));
			str = rmquote(tmp->file_name[i]);
			if (ft_strcmp(content, str) == 0)
			{
				o++;
				if (o == (tmp->heredoc_num))
				{
					free(str);
					free(content);
					content = NULL;
					free(s);
					s = NULL;
					break ;
				}
				i++;
				close(her[1]);
				close(her[0]);
				pipe(her);
			}
			else if (s)
			{
				ft_putstr_fd(s, her[1]);
				ft_putstr_fd("\n", her[1]);
			}
			free(str);
			free(content);
			content = NULL;
			free(s);
			s = NULL;
		}
		tmp->read_her = her[0];
		g_struct->h_sigx = 0;
		close(her[1]);
		o = 0;
		i = 0;
		tmp = tmp->next;
		pipe(her);
	}
	dup2(g_struct->gib, 0);
}

// void    heredoc(t_redir *redirs, t_her * h_b)
// {
// 	int	i;

// 	i = 0;
// }
