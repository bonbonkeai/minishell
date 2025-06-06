#include <../minishell.h>

char	*get_envp(const char *name_path, char **envp)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(name_path);
	i = 0;
	if (!envp)
		error_exit(ERR_ENVP);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name_path, len) == 0 && envp[i][len] == '=' \
			&& envp[i][len + 1] != '\0')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*join_path(const char *dir, const char *name_cmd)
{
	char	*path;
	size_t	len_dir;
	size_t	len_cmd;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(name_cmd);
	path = malloc(len_dir + len_cmd + 2);
	if (!path)
		return (NULL);
	ft_strcpy(path, dir);
	path[len_dir] = '/';
	ft_strcpy(path + len_dir + 1, name_cmd);
	return (path);
}

static void	path_err(char **paths, char *path_envp)
{
	if (!path_envp)
	{
		free_split(paths);
		ft_putstr_fd(ERR_ENVP, 2);
		exit(EXIT_FAILURE);
	}
	if (!paths)
	{
		free(path_envp);
		free_split(paths);
		error_exit("malloc");
	}
	if (!paths[0])
	{
		free(path_envp);
		free_split(paths);
		ft_putstr_fd(ERR_ENVP, 2);
		exit(EXIT_FAILURE);
	}
}
char *ft_getcwd(char *buf, size_t size)
{

}
char	*get_path(char *cmd, char **envp, int i, char **args)
{
    char	*path_envp;
	char	**paths;
	char	*full_path;

	if (!cmd || !envp || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path_envp = get_envp("PATH", envp);
	paths = ft_split(path_envp, ':');
	path_err(paths, path_envp);
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (!full_path)
			return (free_split(paths), error_exit("malloc"), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_split(paths), full_path);
		else if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == -1)
			return (free_split(paths), free(full_path), error_exit(cmd), NULL);
		free(full_path);
	}
	return (ft_putstr_fd(cmd, 2), ft_putstr_fd(ERR_COMMAND, 2), \
			free_split(paths), free_split(args), exit(EXIT_FAILURE), NULL);
}