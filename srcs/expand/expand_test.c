#include "minishell.h"
#include <stdio.h>

void add_env_node(t_env **envp, const char *str)
{
    char *equal_sign = ft_strchr(str, '=');
    char *key;
    char *value;

    if (!equal_sign)
        return;

    key = ft_substr(str, 0, equal_sign - str);
    value = ft_strdup(equal_sign + 1);
    if (!key || !value)
        return ;
    add_new_node(envp, key, value);
    free(key);
    free(value);
}

t_env *make_env(char **envp)
{
    t_env *head = NULL;
    for (int i = 0; envp[i]; i++)
        add_env_node(&head, envp[i]);
    return head;
}

void test_expand(char *input, t_env *env, int status)
{
    char *copy = ft_strdup(input);
    if (!copy)
    {
        printf("Memory allocation failed\n");
        return;
    }
    char *expanded = expand_string(copy, env, status);
    if (!expanded)
        printf("Expansion failed: %s\n", input);
    else
        printf("Input: %-25s → Expanded: \"%s\" (len = %zu)\n",
               input, expanded, ft_strlen(expanded));
    free(expanded);
}


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    int status = 42;
    t_env *env = make_env(envp);

    // 基本变量
    test_expand("$HOME", env, status);
    test_expand("${HOME}", env, status);
    test_expand("$USER", env, status);
    test_expand("$SHELL", env, status);
    printf("\n");

    // 连续变量拼接
    test_expand("$USER$HOME", env, status);
    test_expand("pre$USERpost", env, status);
    printf("\n");

    // 波浪线 ~
    test_expand("~", env, status);
    test_expand("~/Documents", env, status);
    printf("\n");

    // 特殊变量
    test_expand("$?", env, status);
    test_expand("$1", env, status);
    test_expand("$9", env, status);
    printf("\n");

    // 单引号与双引号
    test_expand("'$HOME'", env, status);
    test_expand("\'\"$HOME\"\'", env, status);
    test_expand("\"'$HOME'\"", env, status);
    test_expand("\"$HOME\"", env, status);
    test_expand("\"pre$USER$HOMEpost\"", env, status);
    printf("\n");

    // 空变量
    add_env_node(&env, "EMPTY=");
    test_expand("$EMPTY", env, status);
    printf("\n");

    // 未定义变量
    test_expand("$UNDEFINED_VAR", env, status);
    printf("\n");

    // 空格值
    add_env_node(&env, "SPACES=   ");
    test_expand("$SPACES", env, status);
    printf("\n");

    // 非法变量
    test_expand("$=", env, status);
    printf("\n");

    // 清理
    free_env(env);
    return (0);
}
