#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <stdbool.h>
// # include "../libft/libft.h"

// enum for tokens
enum e_tokens
{
	DOLLAR		= 36,	// $
	WORD		= 2,
	WORD_AST_B	= 3,	// *
	WORD_AST	= 4,	// *
	QUOTE		= 39,	// '
	QUOTE_D		= 34,	// "
	REDIR_OUT	= 62,	// >
	REDIR_IN	= 60,	// <
	REDIR_AP	= 162,	// >>
	REDIR_HD	= 160,	// <<
	DELIM		= 9,
	PIPE		= 124,	// |
	EQUAL		= 61,	// =
	ASTER		= 42,	// *
	AND			= 138,	// &&
	OR			= 224,	// ||
	BR_L		= 40,	// (
	BR_R		= 41,	// )
	AMPER		= 38,	// &
	APOST		= 44,	// `
	BACKSL		= 92,	// '\'
	TRU			= 10,
	FALS		= 11,
	BRACES_L	= 123,	// {
	BRACES_R	= 125	// }
};

// struct for tokens (+ wildcard) linked lists
typedef struct s_node
{
	int				type;
	char			*value;
	int				i;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

// struct for commands
typedef struct s_cmd
{
	char			**cmd;
	int				len_cmd;
	char			*delim;
	int				in;
	char			*in_arg;
	int				out;
	char			*out_arg;
	int				pipe;
	t_node			*wild;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

// linked list for environmental variables
typedef struct s_env
{
	char			*type;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// global structure
typedef struct s_input
{
	int					i;
	int					j;
	char				*tmp;
	char				*type;
	char				*value;
	t_env				*envp_tmp;
	t_node				*node_tmp;
	int					argc;
	int					in;
	int					out;
	char				**envp;
	int					envp_len;
	t_env				*envp_n;
	t_node				*args;
	t_cmd				*cmds;
	char				*buf;
	struct s_builtin	*builtins;
	int					status;
	DIR					*dir;
	pid_t				pid;
	char				**line;
}	t_input;

// struct for builins functions
struct s_builtin
{
	char	*name;
	int		(*func)(t_input *data);
};

// allocation check
void	alloc_check(char **str);
void	alloc_check_small(void *str);
void	alloc_check_token(t_node *new, t_node **node);
void	alloc_check_envp(t_env *new, t_env **node);

// tokens
t_node	*ft_token_new(int type, char *value);
void	ft_token_back(t_node **node, t_node *new);
t_node	*ft_token_del(t_node *node);
void	ft_token_print(t_node *node);
int		ft_token_size(t_node *node);

// envp tokens
t_env	*ft_envp_new(char *type, char *value);
void	ft_envp_back(t_env **node, t_env *new);
t_env	*ft_envp_del(t_env *node);
void	ft_envp_print(t_env *node);
int		ft_envp_size(t_env *node);

// free
void	ft_free(char *str[]);
t_node	*ft_free_token(t_node *node);
t_env	*ft_free_envp(t_env *node);
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_node_elems(t_env *tmp);

// utils
char	*ft_strndup(char const *str, size_t size);
int		error_check(int input, char *str, int n);
int		ft_strstr(char *str, char *to_find);
int		check_charset(char c, char *charset);
void	increase_shlvl(t_input *data);

char	**ft_split_space(char const *s, char *charset);
int		get_next_line(char **line);
int		get_next_line_hd(char **line);

// minishell
void	prompt(t_input *data);

// check_input
int		check_field(char **buf, t_input *data);
int		is_right_buf(char *buf);

// data_init
void	envp_init(t_input *data, char *envp[]);
void	data_init(t_input *data);

// tokenization
void	create_token(t_input *data);

// execute
int		pipex(t_input *data);
void	ft_heredoc(char *limiter, t_cmd *elem);
void	ft_fork(char *argv[], t_input *data);
int		execute(t_input *data);

// execute_utils
char	*ft_strjoin_free(char *rest, char *buf);
char	*ft_charjoin_free(char *line, char b);
char	**get_address(char *cmd[], char *envp[]);
char	*access_check(char *cmd[], char *envp[]);
void	ft_execve(char *argv[], t_input *data);

// builtins
int		yo_pwd(t_input *data);
int		yo_cd(t_input *data);
int		yo_echo(t_input *data);
int		yo_export(t_input *data);
int		yo_env(t_input *data);
int		yo_unset(t_input *data);
int		yo_exit(t_input *data);

// yo_export_utils
void	add_envp(t_input *data, char *type, char *value);

//signals
void	signal_handling(int	signo);

// wildcard
void	asterisks(t_input *data, t_cmd *cmds);

//syntax checker
int		is_the_next_is_word(t_node *args);
t_cmd	*print_syntax_error_cmd(t_node *args);
int		print_syntax_error_bool(t_node *args);

// parsing
int		parsing(t_input *data);

// parsing_utils
t_node	*next_elem(t_node *args);
t_cmd	*init_empty_elem(void);
int		init_in(t_node *args, t_cmd *elem);
int		init_out(t_node *args, t_cmd *elem);
int		get_len_cmd(char **str);

// parsing_utils_2
int		redirection_check(t_node *args, t_cmd *elem);
char	**init_cmd(t_node	*args);

// Readline functions
void	rl_replace_line(const char *text, int clear_undo);

#endif