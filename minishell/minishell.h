/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:54 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/17 00:28:52 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NONE			-1
# define SINGLE_Q		39
# define DOUBLE_Q		34
# define PIPE 			3
# define LIMN 			4
# define LISR 			5
# define APPEND 		6
# define HEREDOC 		7
# define CMD	 		8
# define VARIABLE 		9
# define EXPANDBLE 		10
# define IN_FILE 		12
# define OUT_FILE 		13
# define ARG	 		11
# define HER_ARG 		14
# define SYNT			"Syntax error"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

void	arch_exec(t_stack *tokens);
short	search_linkedl(void);
void	act_execute(t_redir *redirs, t_stack *tokens);
char	**twodimension_dup(char **envp);
short	sig_func(void);
void	set_input(t_redir *redirs, int i);
void	set_output(t_redir *redirs, int i);
void	heredoc(t_redir *redirs);
t_redir	*lstlast_redir(t_redir *lst);
t_redir	*lstnew_redir(void);
void	lstadd_redir(t_redir **lst, t_redir *new);
void	ctrl_d(void);
void	init_gstruct(char **envp, int c, char **v);
void	in_out_dup(t_redir *redirs);
void	export(char **args);
int		chfh(t_stack *token);
short	check_builtins(char	**refined_cmd);
char	**link_toarr(t_stack *tokens);
void	set_delimiters(char **amal, t_stack **tokens, char *commands, int *i);
int		delimiters(char c);
char	*envp_value(char *full_line);
void	reopening(int i, int *pipe_x, int *pipe_y);
char	*envp_name(char *full_line);
char	*ft_strjoin2(char *s1, char *s2);
char	*join_path(char *cmd_token);
int		lexer(char *commands, t_stack **tokens);
size_t	pipe_counter(t_stack *tokens);
char	**refine(t_stack *tokens);
void	skip_space(int *i, char *commands);
short	closing_quote(char *line, int i, short quote);
size_t	pipe_counter(t_stack *tokens);
void	set_pipe(char **amal, int *i, t_stack **tokens);
void	set_double(char **amal, int *i, char *line, t_stack *token);
void	set_single(char **amal, int *i, char *line);
void	set_aadi(char **amal, int *i, char *line, t_stack **tokens);
void	set_right(char **amal, int *i, char *commands, t_stack **tokens);
void	set_left(char **amal, int *i, char *commands, t_stack **tokens);
char	*ft_strjoin(char *s1, char s2);
void	envp_to_linked_list(char **array);
t_redir	*creat_cmdlist(int pipe_c);
t_redir	*set_dir_type(t_stack *tokens, t_redir	*list);
char	*var_extract(char *line);
int		check_pipe(t_stack *cmds);
int		parsing(t_stack **tokens);
void	pipe_sys(size_t i, int *pipe_x, int *pipe_y, size_t pipe_num);
void	fst_cmd(int *pipe_x, int *pipe_y);
void	mdle_cmd(int *pipe_x, int *pipe_y, int i);
void	lst_cmd(int *pipe_x, int *pipe_y, int i);
short	single(t_stack *tokens);
char	**refine(t_stack *tokens);
char	**sgl_refine(t_stack *tokens, int i);
void	builtin_exec(t_redir *redirs, short mode);
short	multiple( t_redir	*redirs);
void	expandwithtokens(char **amal, int *i, char *line, t_stack **tokens);
void	expandstatus(char **amal, int *i);
void	absocute(t_redir *redirs, t_stack *tokens);
void	expandnormal(char **amal, int *i, char *line);
void	free_2d(char	**split);
void	pwd(void);
void	cd(t_redir *redirs);
void	echo(t_redir *redirs);
void	env(void);
void	unset(char **args);
int		comparethething(char *s1, char *s2);
void	set_double2(char **amal, int *i, char *line);
void	set_single2(char **amal, int *i, char *line);
int		set_amal_adi(char *commands, int *i, char **amal, t_stack **tokens);
t_redir	*info_dump(t_stack *tokens, t_redir *list);
int		valid_dir(char **directory);
void	set_type(t_stack *tokens);
void	closure(int *pipe_x, int *pipe_y);
void	freet_redir(t_redir **redirs);
void	freet_stack(t_stack **tokens);
void	fill_list_infdump(t_redir *list, t_stack *tokens, int fc, int h_f_c);
void	fill_refined(t_stack **temp, char **refined_cmd);
int		chfh2(t_stack *token);
int		redirection_err(t_stack *tokens);
int		piping_err(t_stack *tokens);
void	shrink_exptokens(int *found, char **s, t_stack *temp);
int		checkequal(char *v);
void	export(char **args);
void	unset(char **args);
int		checkexarg(char *v);
char	*thebefeq(char *s);
void	deletenode(t_stack **head, char *element);
void	addexplist(char **args);
void	exp_normal_exp(t_stack *temp, char **amal, int *found);
void	isdir_ismultiple(t_redir *redirs, t_stack *tokens);
void	error_func(t_redir *redirs, t_stack *tokens);
void	free_absocute(t_redir **redirs2, t_stack **tokens, int *p_x, int *p_y);
void	process_monitor(int *pid_arr, int count);
void	err_exit(int n_exit, t_redir *redirs, t_stack *tokens, short mode);

#endif