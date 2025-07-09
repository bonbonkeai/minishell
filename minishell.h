/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:51:40 by jdu               #+#    #+#             */
/*   Updated: 2025/07/09 14:46:06 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>
# include <sys/ioctl.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define GREEN  "\001\033[0;32m\002"
# define BLUE   "\001\033[0;34m\002"
# define DEFAULT "\001\033[0m\002"
# define CYAN_BOLD_UNDERLINE "\001\033[1;4;36m\002"

# define ERR_COMMAND ": command not found"
# define ERR_SQUOTE "minishell: unexpected EOF while looking for matching '\n"
# define ERR_DQUOTE "minishell: unexpected EOF while looking for matching \"\n"
# define ERR_DOUBLE_PIPE "minishell: syntax error near unexpected token `||'\n"
# define ERR_NEWLINE "minishell: syntax error near unexpected token `newline'\n"
# define ERR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERR_TOKEN "minishell: syntax error near unexpected token `%s'\n"
# define ERR_TOKEN_C "minishell: syntax error near unexpected token `%c'\n"
# define MES_E "export: usage: export [-fn] [name[=value] ...] or export -p\n"
# define ERRMAL "export: memory allocation failed"
# define ERR_SIGNAL "minishell: warning: here-document at \
line 1 delimited by end-of-file (wanted `ok')\n"
# define ERR_PWD "minishell: pwd: %s: invalid option \npwd: usage: pwd [-LP]\n"
# define ERR_ENV_I "This input is not accecpted\n"
# define ERR_ENV "env: invalid option `%s'\nTry \
'env --help' for more information.\n"

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

extern int	g_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}		t_env;

typedef struct s_pipe
{
	int	fd[2];
}		t_pipe;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_INPUT,
	T_OUTPUT,
	T_APPEND,
	T_HEREDOC,
}		t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;	
}		t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			*pth;
	char			**args;
	char			*infile;
	char			*outfile;
	char			*heredoc_limiter;
	int				fd_in;
	int				fd_out;
	int				append;
	int				heredoc;
	char			**red;
	int				heredoc_expand;
	int				heredoc_fd;
	int				pid;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_redir
{
	char	*file;
	int		type;
}		t_redir;

typedef struct s_expansion
{
	char	*str;
	char	*buf;
	int		size;
	int		len;
	int		i;
	int		k;
	int		in_squote;
	int		in_dquote;
	char	*env_val;
	char	*var_name;
	char	*exit_status;
	int		illegal_type;
	char	*error_char;
	int		status;
}		t_expansion;

typedef struct s_shell
{
	t_env	*env;
	char	**paths;
	char	*username;
	char	*trimmed_prompt;
	char	*default_home;
	int		status;
	t_pipe	old_pipe;
	t_pipe	new_pipe;
	t_cmd	*cmd;
	t_token	*token_list;
	t_cmd	*curr_cmd;
	int		should_expand;
}		t_shell;

typedef enum e_suffix_type
{
	SUFFIX_OK,
	SUFFIX_PIPE,
	SUFFIX_REDIR,
	SUFFIX_SYNTAX_ERROR,
	SUFFIX_HISTORY,
	SUFFIX_BACKGROUND,
	SUFFIX_SEMICOLON
}		t_suffix_type;

//init
t_env			*add_new_node(t_env **envp, const char *key, \
				const char *value, int exported);
t_env			*init_env(char **envp);
void			parse_and_add(char *entry, t_env **env);
void			handle_empty_env(t_env **env);
char			*extract_username(t_env *env);
char			*get_env_value(t_env *env, char *key);
void			free_env(t_env *env);
char			**init_path_array(t_env *env);
void			free_paths(char **paths);
t_shell			*init_shell(char **envp);
void			free_shell(t_shell *sh);
t_cmd			*init_cmd(void);
void			free_cmd_list(t_cmd *head);
void			free_cmd(t_cmd *cmd);
int				init_expand(t_expansion *exp, char *input, int status);
void			free_expansion(t_expansion *exp);
void			rm_void_from_cmd(t_cmd *command, int i, int j, int num);
void			rm_void_tab_cmd(t_cmd **tab_cmd);

//signal
void			signal_hiding(void);
void			signal_showing(void);
void			signal_sigint(int sig);
int				event(void);
void			signal_handle(void);
void			signal_default(void);

//promt
char			*ft_getcwd(char *buf, size_t size);
char			*build_home(t_shell *shell);
char			*build_prompt(t_shell *shell);

//lexer
int				is_too_many_char(const char *input, int i, char c);
char			next_non_space(const char *input, int i);
int				check_heredoc_redir_conflict(const char *input, int i);
int				check_long_redir_sequence(const char *input, int i);
int				check_pipe_conflict(const char *input, int i);
int				check_redir_newline_end(const char *input, int i);
int				check_triple_redir(const char *input, int i);
int				check_too_many_redir(const char *input, int i);
int				check_spacing_errors(const char *input, int i);
int				check_double_pipe(const char *input, int i);
int				check_mixed_combos(const char *input, int i);
int				is_invalid_operator(const char *input, int i);
int				lexer(t_shell *shell);
int				is_empty_command(const char *input);
int				check_syntax(const char *input);
void			toggle_quote(char ch, int *in_squote, int *in_dquote);
void			syntax_error(char unexpected);
void			syntax_error_pipex(char *unexpected);
int				check_quotes_closed(int in_squote, int in_dquote);
int				is_pipe_error(const char *s);
void			syntax_error_newline(void);

//tokenizer
t_token			*create_token(const char *content, t_token_type type);
void			add_token(t_token **head, t_token *new);
t_token_type	get_token_type(char *s);
int				get_operator_token(const char *line, int i, \
				t_token **tokens);
int				consume_word(const char *line, int i);
int				get_word_token(const char *line, int i, t_shell *sh);
void			tokenize_prompt(t_shell *sh, const char *line);
void			free_tokens(t_token *tok);
int				check_token_syntax(t_token *t);

//parsing
t_cmd			*parser(t_shell *sh);
int				check_pipe(t_token *tokens);
t_cmd			*parse_one_command(t_token **token_list);
void			add_arg(t_cmd *cmd, const char *arg);
int				is_cmd_valide(t_cmd *cmd);
t_cmd			*build_cmd_list(t_token *token_list);
bool			handle_token(t_cmd *cmd, t_token **token_list);
int				copy_old_args(char **dest, char **src, int len);
char			**duplicate_args(char **old_args, int len, const char *arg);

//redirection
void			handle_input_redir(t_cmd *cmd, char *op, char *file);
void			handle_output_redir(t_cmd *cmd, char *op, char *file);
void			resolve_redir(t_shell *sh, t_cmd *cmd, int *storage);
void			add_redir(t_cmd *cmd, char *op, char *target);
int				is_red_type(t_token_type type);
void			apply_input_red(t_shell *sh, int *storage);
void			apply_output_red(t_shell *sh, int *storage);
bool			touch_all_output_files(t_cmd *cmd);
int				append_op_and_target(char **new_red, int len, \
				char *op, char *target);
char			**init_new_redir_array(t_cmd *cmd, int len);
int				count_redirs(char **red);
void			safe_exit_with_io_close(t_shell *sh, int *storage, int code);
void			process_input_redir(t_shell *sh, char *op, \
			char *file, int *storage);
void			apply_heredoc_fd(t_shell *sh, t_cmd *cmd, int *storage);
void			process_single_redirection(t_shell *sh, char *op, \
			char *file, int *storage);
void			close_all_heredoc_fd(t_cmd *cmd_list);

//expander
int				expand_tab(char **tab, t_shell *sh, \
				t_suffix_type *out_type, char *error_char);
int				expand_vars(t_shell *sh, t_suffix_type *out_type, \
				char *error_char);
int				expand_all(t_shell *sh, t_suffix_type *out_type, \
				char *error_char);
char			*expand_string(char *str, t_shell *sh, t_suffix_type *out_type, \
				char *error_char);
int				has_illegal_expansion(t_suffix_type type, char ch);
int				handle_illegal_dollar(const char *input, t_expansion *exp);
int				handle_dollar(char *input, t_expansion *exp, t_env *lst_env);
int				handle_braces(t_expansion *exp, t_env *lst_env);
char			*extract_var_name(const char *input, int start, \
				int *matched_len);
int				append_str_to_buffer(t_expansion *exp, const char *str);
t_suffix_type	get_suffix_type(char c);
void			handle_single_quote(t_expansion *exp);
int				handle_double_quote(t_expansion *exp, t_env *env);
int				append_char(t_expansion *exp, char c);
int				valid_exp(int c);
int				is_quote(char c);
int				handle_buffer(t_expansion *exp);
int				handle_exit_status(t_expansion *exp);
int				append_str(t_expansion *exp);
int				append_env(t_expansion *exp);
char			*expand_buffer(char *old_buffer, int *size);
int				handle_env_var(t_expansion *exp, t_env *lst_env);
int				has_quote(const char *str);
int				should_heredoc_expand(const char *delimiter);
char			*expand_heredoc_line(char *line, t_shell *sh);
char			*process_heredoc_content(char *delimiter, t_shell *sh);
char			*merge_quoted_string(const char *limiter);
char			*get_heredoc_content(char *target, char *lim, t_shell *sh);
char			*set_should_expand(t_shell *sh, char *target);
int				expand_heredoc_in_cmd_list(t_shell *sh, \
				t_suffix_type *out_type, char *error_char);
char			*expand_var_here(char *input, t_shell *sh);
int				expand_var_here_check(char *input, \
				t_expansion *exp, t_shell *sh);
char			*remove_quotes(const char *str);
void			cleanup_current_cmd(t_shell *sh);
char			*expand_home(char *str, t_shell *sh);
char			*handle_expand_error(t_expansion *exp, \
				t_suffix_type *out_type, char *error_char);
int				handle_question_mark(t_expansion *exp);
int				handle_digit_after_dollar(const char *input, t_expansion *exp);
int				handle_illegal_or_braces(const char *input, \
				t_expansion *exp, t_env *lst_env);
int				check_and_handle_suffix(const char *input, \
				t_expansion *exp, int matched_len);
int				expand_and_append_value(t_expansion *exp, \
				const char *value, int matched_len);
bool			is_heredoc(t_cmd *cmd);
int				assign_cmd_names(t_cmd *cmd);
bool			read_heredoc_loop(char **buffer, size_t *buf_len, \
				char *delimiter, t_shell *sh);
bool			process_heredoc_line(char **buffer, size_t *buf_len, \
				char *line, t_shell *sh);
char			*strip_outer_quotes(const char *s);

//builtin
int				is_valid_var_name(char *var);
int				builtin_unset(t_shell *sh, char **argv);
int				builtin_pwd(t_shell *sh);
void			env_set_var(char *key, char *value, t_shell *sh);
int				builtin_export(char **argv, t_shell *sh);
int				builtin_exit(t_shell *sh, char **argv);
int				builtin_env(t_shell *sh);
int				builtin_echo(char *args[]);
int				builtin_cd(t_shell *shell, char **argv);

//executor
int				executor(t_shell *shell);
int				is_directory(const char *path);
void			print_cmd_error(char *cmd, char *msg);
int				if_cmd_builtin(t_shell *sh);
int				if_cmd_start(t_cmd *cmd);
int				if_cmd_simple(t_cmd *cmd);
void			exec_simple_exit(t_shell *sh);
int				exec_wait_pid(pid_t pid);
int				exec_simple(t_shell *sh);
int				execve_bin(t_shell *sh);
int				exec_pipe(t_shell *sh);
void			pipe_fork_child(t_shell *sh, t_pipe *new_pipe, \
			t_pipe *old_pipe, int last);
void			pipe_for_parent(t_pipe *new_pipe, t_pipe *old_pipe);
void			safe_close_all_pipes(t_shell *shell);
int				allocate_builtin(t_shell *shell);
int				apply_store_and_red(t_shell *sh, int storage[2]);
void			recover_io_and_close(int storage[2]);
int				exec_builtin_main(t_shell *sh, t_cmd *curr_cmd);
void			touch_all_output_files_in_list(t_cmd *cmd_list);
int				exec_simple_pipe(t_shell *sh);
void			exec_child(t_shell *sh, t_cmd *curr, int status);
int				handle_check_prexec(t_shell *sh, t_cmd *curr);
void			exec_child(t_shell *sh, t_cmd *curr, int status);
int				exec_exit_status(int mode, int new_status);
int				check_exec_if_builtin(t_shell *sh, t_cmd *curr);
int				wait_for_allpid(pid_t last_pid);
void			handle_check(t_shell *sh, t_cmd *curr);

//utils
void			ft_perror_export(char *arg);
void			bubble_sort_env(t_env **arr, int size);
char			**get_args(t_shell *sh);
char			*get_path(t_shell *sh);
char			**get_env_variables(t_shell *sh);
void			export_print_env(t_shell *sh);
void			env_set_value(t_shell *sh, char *key, char *value, int append);
void			split_var_asin(char *arg, char **key, char **value, int *ap);
bool			save_std_io(int storage[2]);
bool			restore_std_io(int storage[2]);
int				check_standard_fd(int fd);
int				check_cmd_standard(t_shell *sh);
int				if_bin_access(char **bins, t_shell *sh);
int				if_abs_bin_access(char *command);
char			*get_env_var_value(t_shell *sh, char *name);

//main
void			process_input(t_shell *shell, char *input);
void			minishell_loop(t_shell *shell);
int				main(int argc, char **argv, char **envp);

#endif
