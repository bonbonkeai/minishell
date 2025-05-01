#ifndef PHILO_H
# define PHILO_H

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

# define PATH_MAX 4096
# define ERR_COMMAND ": command not found\n"
# define ERR_ENVP "Evironment variables not available\n"

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}               t_env;

typedef struct s_shell
{
    t_env *env;
    char **paths;
    char *username;
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
    char **args;
    char *infile;
    char *outfile;
    int append;
    int heredoc;
    char **red;
    struct s_cmd *next;
    
}               t_cmd;

typedef struct s_redir
{
    char *file;
    int     type;
}               t_redir;



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

//promt
char *join4str(char *s1, char *s2, char *s3, char *s4);
char *last_dir(const char *path);


char *ft_getcwd(char *buf, size_t size);


//parsing
void    add_redir(t_cmd *cmd, char *op, char *target);
t_cmd   *parse_one_command(t_token **token_list);
t_cmd   *parser(t_token *token_list);
void    add_arg(t_cmd *cmd, const char *arg);
void    resolve_redir(t_cmd *cmd);
int is_cmd_valide(t_cmd *cmd);
int check_pipe(t_token *tokens);

#endif