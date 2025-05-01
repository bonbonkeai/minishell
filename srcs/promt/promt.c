#include <../minishell.h>

//为了拼接4个字符串，因为readline的promt是长这样：jdu&jinhuang@minishell~/Documents$。它会由用户名+@+minishell+最后路径的目录名+$（结尾提示符），也就是4个字符串。
char *join4str(char *s1, char *s2, char *s3, char *s4)
{
    size_t total_len;
    char *res;

    total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4);
    res = malloc(total_len + 1);
    if (!res)
        return (NULL);
    ft_strcpy(res, s1);
    ft_strcpy(res, s2);
    ft_strcpy(res, s3);
    ft_strcpy(res, s4);
}

//给一个路径返回路径中的最后一段目录名，这可以在我们的minishell中的提示符显示为“jdu&jinhuang@minishell/Doucuments$”，只提取当前路径中的最后一个目录，这样利于用户的阅读，
char *last_dir(const char *path)
{
    const char *last;

    if (!path || !*path)
        return (NULL);
    last = ft_strrchr(path, '/');
    if (last)
        return (ft_strdup(last + 1));
    else
        return (ft_strdup(last));
}
