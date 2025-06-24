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

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

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

// typedef struct s_shell
// {
//     t_env *env;
//     char **paths;
//     char *username;
//     char    *trimmed_prompt;
//     int     status;
//     t_pipe  old_pipe;
//     t_pipe  new_pipe;

// }              t_shell;

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
    char *heredoc_limiter;
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
    char    *str;
    char    *buf;
    int     size;
    int     len;
    int     i;
    int     k;
    int     in_squote;
    int     in_dquote;
    char    *env_val;
    char    *var_name;
    char    *exit_status;
    int     illegal_type;
    char    *error_char;
    int		status;
} t_expansion;

typedef struct s_shell
{
    t_env *env;
    char **paths;
    char *username;
    char    *trimmed_prompt;
    int     status;
    t_pipe  old_pipe;
    t_pipe  new_pipe;
    t_cmd *cmd;
    t_token *token_list;
    t_cmd *curr_cmd;

}              t_shell;

typedef enum e_suffix_type
{
    SUFFIX_OK,
    SUFFIX_PIPE,
    SUFFIX_REDIR,
    SUFFIX_SYNTAX_ERROR,
    SUFFIX_HISTORY,
    SUFFIX_BACKGROUND,
    SUFFIX_SEMICOLON
}   t_suffix_type;

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
// int		init_expand(t_expansion *exp);
int init_expand(t_expansion *exp, char *input, int status);
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
char *ft_getcwd(char *buf, size_t size);
char *build_home(t_shell *shell);
char *build_prompt(t_shell *shell);

//lexer
int is_too_many_char(const char *input, int i, char c);
char next_non_space(const char *input, int i);
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
int consume_word(const char *line, int i);
// int get_word_token(const char *line, int i, t_token **tokens);
int get_word_token(const char *line, int i, t_shell *sh);
// t_token *tokenize_prompt(const char *line);
void tokenize_prompt(t_shell *sh, const char *line);
void free_tokens(t_token *tok);
int check_token_syntax(t_token *t);

//parsing
// t_cmd *parser(t_token *token_list);
t_cmd *parser(t_shell *sh);
int check_pipe(t_token *tokens);
t_cmd *parse_one_command(t_token **token_list);
void add_arg(t_cmd *cmd, const char *arg);
int is_cmd_valide(t_cmd *cmd);

//redirection
void handle_input_redir(t_cmd *cmd, char *op, char *file);
void handle_output_redir(t_cmd *cmd, char *op, char *file);
void resolve_redir(t_cmd *cmd);
void    add_redir(t_cmd *cmd, char *op, char *target);
int	is_red_type(t_token_type type);
void	apply_input_red(t_shell *sh);
void	apply_output_red(t_shell *sh);
void	apply_red(t_shell *sh);

//expander
int expand_tab(char **tab, t_shell *sh, t_suffix_type *out_type, char *error_char);
int expand_single(char **str, t_shell *sh, t_suffix_type *out_type, char *error_char);
int expand_vars(t_shell *sh, t_suffix_type *out_type, char *error_char);
int expand_all(t_shell *sh, t_suffix_type *out_type, char *error_char);
char *expand_string(char *str, t_shell *sh, t_suffix_type *out_type, char *error_char);
int has_illegal_expansion(t_suffix_type type, char ch);
int handle_illegal_dollar(char *input, t_expansion *exp);
int handle_dollar(char *input, t_expansion *exp, t_env *lst_env);
int	handle_braces(t_expansion *exp, t_env *lst_env);
char *extract_var_name(const char *input, int start, int *matched_len);
int append_str_to_buffer(t_expansion *exp, const char *str);
t_suffix_type get_suffix_type(char c);
void handle_single_quote(t_expansion *exp);
int handle_double_quote(t_expansion *exp, t_env *env);
int append_char(t_expansion *exp, char c);
int valid_exp(int c);
int handle_buffer(t_expansion *exp);
int handle_exit_status(t_expansion *exp);
int append_str(t_expansion *exp);
int append_env(t_expansion *exp);
char *expand_buffer(char *old_buffer, int *size);
int handle_env_var(t_expansion *exp, t_env *lst_env);
int has_quote(const char *str);
int should_heredoc_expand(const char *delimiter);
char *expand_heredoc_line(char *line, t_shell *sh);
char	*process_heredoc_content(char *delimiter, t_shell *sh, int should_expand);
int is_quote(char c);
char	*merge_quoted_string(const char *limiter);
int	expand_heredoc_in_cmd_list(t_shell *sh);
char *expand_var_here(char *input, t_shell *sh);
int expand_var_here_check(char *input, t_expansion *exp, t_shell *sh);
char *remove_quotes(const char *str);
void cleanup_current_cmd(t_shell *sh);

char *expand_home(char *str, t_shell *sh);
char *handle_expand_error(t_expansion *exp, t_suffix_type *out_type, char *error_char);

//builtin
int	is_valid_var_name(char *var);
int	builtin_unset(t_shell *sh, char **argv);
int	builtin_pwd(void);
void	env_set_var(char *key, char *value, t_shell *sh);
int	builtin_export(char **argv, t_shell *sh);
int	builtin_exit(char **argv);
int	builtin_env(t_shell *sh);
int	builtin_echo(char *args[]);
int	builtin_cd(t_shell *shell, char **argv);

//executor
bool	executor(t_shell *shell);
int	is_directory(const char *path);
void	print_cmd_error(char *cmd, char *msg);
int	if_cmd_builtin(t_shell *sh);
// int	if_cmd_start(t_shell *sh);
int	if_cmd_start(t_cmd *cmd);
// int	if_cmd_simple(t_shell *sh);
int	if_cmd_simple(t_cmd *cmd);
void	exec_simple_exit(t_shell *sh);
int	exec_wait_pid(pid_t pid);
int	exec_simple(t_shell *sh);
int	execve_bin(t_shell *sh);
int	exec_pipe(t_shell *sh);
// void	pipe_fork_child(t_pipe *new_pipe, t_pipe *old_pipe);
void	pipe_fork_child(t_pipe *new_pipe, t_pipe *old_pipe, int last);
void	pipe_for_parent(t_pipe *new_pipe, t_pipe *old_pipe);
void	safe_close_all_pipes(t_shell *shell);
int	allocate_builtin(t_shell *shell);
int	apply_store_and_red(t_shell *sh, int storage[2]);
void	recover_io_and_close(int storage[2]);
int	exec_builtin_main(t_shell *sh);


//utils
char	**get_args(t_shell *sh);
char	*get_path(t_shell *sh);
char	**get_env_variables(t_shell *sh);
bool	save_std_io(int storage[2]);
bool	restore_std_io(int storage[2]);
int	check_standard_fd(int fd);
int	check_cmd_standard(t_shell *sh);
int	if_bin_access(char **bins, t_shell *sh);
int	if_abs_bin_access(char *command);
char	*get_env_var_value(t_shell *sh, char *name);

//main
void    process_input(t_shell *shell, char *input);
void minishell_loop(t_shell *shell);
int	main(int argc, char **argv, char **envp);



#endif