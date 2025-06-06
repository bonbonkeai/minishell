#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>
# include <termios.h>

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

# define GREEN  "\001\033[0;32m\002"
# define BLUE   "\001\033[0;34m\002"
# define DEFAULT "\001\033[0m\002"

# define ERR_COMMAND ": command not found\n"
# define ERR_ENVP "Evironment variables not available\n"

# define OPERATOR "|<>"
# define TRUE 1
# define FALSE 0

# define REDIN     1
# define HEREDOC   2
# define REDOUT    3
# define APPEND    4
# define TEXT      0

# define INIT_SIZE 64
# define FACTOR     2

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}               t_env;

typedef struct s_pipe
{
    int   fd[2];
    int fd_in;
    int fd_out;
}               t_pipe;

typedef struct s_shell
{
    t_env *env;
    char **paths;
    char *username;
    char    *trimmed_prompt;
    int     status;
    t_pipe  old_pipe;
    t_pipe  new_pipe;

}              t_shell;

typedef enum e_token_type
{
    T_WORD,
    T_PIPE,
    T_INPUT,
    T_OUTPUT,
    T_APPEND,
    T_HEREDOC,
}               t_token_type;

typedef struct s_token
{
    char *content;
    t_token_type type;
    struct s_token *next;
    
}                   t_token;

typedef struct s_cmd
{
    char *cmd;
    char *pth;
    char **args;
    char *infile;
    char *outfile;
    int fd_in;
    int fd_out;
    int append;
    int heredoc;
    char **red;
    int heredoc_expand;
    int heredoc_fd;
    int pid;
    struct s_cmd *next;
    
}               t_cmd;

typedef struct s_redir
{
    char *file;
    int     type;
}               t_redir;

typedef struct s_expansion
{
	char	*result;
	int		size;
	int		len;
	int		i;
	int		k;
	int		in_squote;
	int		in_dquote;
	char	*exit_status;
	char	*env_val;
	char	var_name[1024];
}	t_expansion;

//init
t_env   *add_new_node(t_env **envp, const char *key, const char *value);
t_env   *init_env(char **envp);
void    parse_and_add(char *entry, t_env **env);
void    handle_empty_env(t_env **env);
char *extract_username(t_env *env);
char *get_env_value(t_env *env, const char *key);
void    free_env(t_env *env);
char    **init_path_array(t_env *env);
void    free_paths(char **paths);
t_shell *init_shell(char **envp);
void    free_shell(t_shell *sh);
t_cmd   *init_cmd(void);
void    free_cmd_list(t_cmd *head);
void    free_cmd(t_cmd *cmd);
int		init_expansion(t_expansion *exp);
void	free_expansion(t_expansion *exp);
void rm_void_from_cmd(t_cmd *command, int i, int j, int num);
void rm_void_tab_cmd(t_cmd **tab_cmd);

//signal
void	signal_hiding(void);
void	signal_showing(void);
void	signal_sigint(int sig);
void	signal_eof(void);
void	signal_handle(void);
void	signal_handle_fork(void);
void	signal_default(void);
void	signal_heredoc(void);
void	sigint_hl_heredoc(int sig);
void	check_fork_signal(int statloc);

//promt
//char *join4str(char *s1, char *s2, char *s3, char *s4);
//char *last_dir(const char *path);
char *ft_getcwd(char *buf, size_t size);
char *build_home(t_shell *shell);
char *build_prompt(t_shell *shell);

//lexer
int lexer(t_shell *shell);
int is_empty_command(const char *input);
int is_specific_case(t_shell *s);
int check_syntax(const char *input);
void toggle_quote(char ch, int *in_squote, int *in_dquote);
int is_invalid_operator(const char *input, int i);
void syntax_error(char unexpected);
void syntax_error_pipex(char *unexpected);
int check_quotes_closed(int in_squote, int in_dquote);
int is_pipe_error(const char *s);
void	syntax_error_newline(void);

//tokenizer
t_token *create_token(const char *content, t_token_type type);
void add_token(t_token **head, t_token *new);
t_token_type get_token_type(char *s);
int get_operator_token(const char *line, int i, t_token **tokens);
int get_word_token(const char *line, int i, t_token **tokens);
t_token *tokenize_prompt(const char *line);
void free_tokens(t_token *tok);
int check_token_syntax(t_token *t);

//parsing
void    add_redir(t_cmd *cmd, char *op, char *target);
t_cmd   *parse_one_command(t_token **token_list);
t_cmd   *parser(t_token *token_list);
void    add_arg(t_cmd *cmd, const char *arg);
void    resolve_redir(t_cmd *cmd);
int is_cmd_valide(t_cmd *cmd);
int check_pipe(t_token *tokens);

//redirection
int	is_red_type(t_token_type type);
void handle_input_redir(t_cmd *cmd, char *op, char *file);
void handle_output_redir(t_cmd *cmd, char *op, char *file);
void	apply_red(t_cmd *cmd);

//expander
char *expand_tilde(char *input, t_env *lst_env);
void expand_tab(char **tab, t_env *env_head, int status);
void expand_array(char **array, t_env *env, int status);
void expand_all(t_cmd **cmds, t_env *env_head, int status);
char	*expand_string(char *str, t_env *lst_env, int status);
//expand:joint&buffer
char *expand_buffer(char *old_buffer, int *size);
int append_str(t_expansion *exp);
int append_env(t_expansion *exp);
//expand:variable
int	handle_dollar(char *input, t_expansion *exp, t_env *lst_env, int status);
int	handle_braces(t_expansion *exp, t_env *lst_env);
int handle_exit_status(t_expansion *exp, int status);
int handle_env_var(t_expansion *exp, t_env *lst_env);
int valid_exp(int c);
//expand:here_doc
int check_heredoc_expand(const char *delimiter);
char *strip_quotes_if_needed(const char *str);
int should_expand_heredoc(const char *delimiter);
char *expand_heredoc_line(const char *line, t_env *env);
char	*process_heredoc_content(char *delimiter, t_env *env, int should_expand);
int	expand_heredocs_in_cmd_list(t_cmd *cmd_list, t_env *env);
char *expand_var_here(char *input, t_env *lst_env, int status);
int expand_var_here_check(char *input, t_expansion *exp, t_env *lst_env, int status);

//executor
int	exec_simple(t_cmd *cmd, t_env *env);
int	execve_bin(t_cmd *cmd, t_env *env);
int	if_cmd_builtin(t_cmd *cmd);
int	if_cmd_start(t_cmd *cmd);
int	if_cmd_simple(t_cmd *cmd);
int	exec_wait_pid(pid_t pid);
int	exec_pipe(t_cmd *cmd, t_shell *shell);
bool executor(t_cmd *cmd, t_shell *shell);
void	exec_simple_exit(t_cmd *cmd);
char *join_path_cmd(char *path, char *cmd);
void	pipe_fork_child(t_pipe *new_pipe, t_pipe *old_pipe);
void	pipe_for_parent(t_pipe *new_pipe, t_pipe *old_pipe);
void	initialize_pipe(t_shell *shell);
void	safe_close_all_pipes(t_shell *shell);

//utils
char	**get_args(t_cmd *cmd);
char	*get_path(t_cmd *cmd, t_env *env);
char    **get_env_variables(t_env *env);
int	check_standard_fd(int fd);
int	check_cmd_standard(t_cmd *cmd);
int	if_bin_access(char **bins, t_cmd *cmd);
int	if_abs_bin_access(char *command);
char	*get_env_var_value(t_env *env, char *name);

//main
void	minishell_loop(t_shell *shell);
int	main(int argc, char **argv, char **envp);

#endif