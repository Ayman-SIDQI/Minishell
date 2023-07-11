/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:53:51 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/17 10:51:23 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_redir
{
	char			**refined_cmd;
	char			**file_name;
	int				*type;
	int				heredoc_num;
	int				read_her;
	struct s_redir	*prev;
	struct s_redir	*next;
}				t_redir;

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*prev;
	struct s_list	*next;
}					t_stack;

typedef struct s_shell
{
	int		ex_st;
	int		status;
	t_stack	*env_list;
	char	*env_copy;
	int		std_in;
	int		std_out;
	int		exited;
	int		h_sigx;
	int		h_sigy;
	char	**envp;
	char	**split_paths;
	//=========== heredoc stuff 👇🏻
	char	*content;
	char	*s;
	int		her[2];
	int		o;
	int		gib;
	t_redir	*tmp;
	char	*str;
	//absocute
	int		pipe_x[2];
	int		pipe_y[2];
	int		*pid_arr;
}t_shell;

typedef struct s_her
{
	char	*content;
	char	*s;
	int		her[2];
	int		o;
	int		gib;
	t_redir	*tmp;
	char	*str;
}t_her;

extern t_shell	*g_struct;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(const char *s, int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
long long	ft_atoi(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strrchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putendl_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
t_stack		*ft_lstnew(char *str, short type);
void		ft_lstadd_front(t_stack **lst, t_stack *new);
int			ft_lstsize(t_stack *lst);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
t_stack		*ft_lstlast(t_stack *lst);
void		ft_lstadd_back(t_stack **lst, t_stack *new);
void		ft_lstclear(t_stack **lst, void (*del)(void *));
int			ft_strlen2(char *s);
int			ft_strcmp2(char *s1, char *s2);
int			doublelengh(char **s);
char		*ft_strjoin2(char *s1, char *s2);

#endif
