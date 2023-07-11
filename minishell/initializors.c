/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:32:18 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/16 23:17:32 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ctrl_d(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_struct->exited = 0;
	g_struct->ex_st = 1;
	printf("exit\n");
}

void	init_gstruct(char **envp, int c, char **v)
{
	(void)c;
	(void)v;
	g_struct = (t_shell *)malloc(sizeof(t_shell));
	if (!g_struct)
		return ;
	g_struct->exited = 1;
	g_struct->std_in = dup(0);
	g_struct->std_out = dup(1);
	g_struct->h_sigx = 0;
	g_struct->h_sigy = 0;
	g_struct->envp = twodimension_dup(envp);
	g_struct->env_list = NULL;
	envp_to_linked_list(envp);
}

void	my_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGINT)
	{
		if (g_struct->h_sigx == 0)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_struct->ex_st = 1;
		}
		else
		{
			close(0);
			printf("\n");
			g_struct->h_sigy = 1;
			g_struct->ex_st = 1;
		}
	}
}

short	sig_func(void)
{
	struct sigaction	action;

	action.sa_handler = &my_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) == -1 \
	|| sigaction(SIGQUIT, &action, NULL) == -1)
		return (1);
	return (0);
}
