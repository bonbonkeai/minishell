#include "minishell.h"

int init_expansion(t_expansion *exp)
{
    if (!exp)
        return (0);
    exp->size = INIT_SIZE;
    exp->result = (char *)malloc(exp->size * sizeof(char));
    if (!exp->result)
        return (0);
    exp->len = 0;
    exp->i = 0;
    exp->k = 0;
    exp->in_squote = 0;
    exp->in_dquote = 0;
    exp->exit_status = NULL;
    exp->env_val = NULL;
    exp->str = NULL;
    return (1);
}

void	free_expansion(t_expansion *exp)
{
	if (!exp)
		return ;
	if (exp->result)
		free(exp->result);
	if (exp->exit_status)
		free(exp->exit_status);
	if (exp->env_val)
		free(exp->env_val);
}

/* void rm_void_from_cmd(t_cmd *command, int i, int j, int num)
{
    char **tmp_tab;

    tmp_tab = command->cmd;
    while (command->cmd[i])
    {
        if (!strcmp("", command->cmd[i]))
            i++;
        else
            break;
    }
    if (i == num)
        return ;
    command->cmd = malloc((num - i + 1) * sizeof(char *));
    if (!command->cmd)
        return (command->cmd = tmp_tab, (void)0);
    while (tmp_tab[i])
    {
        command->cmd[j] = ft_strdup(tmp_tab[i]);
        if (!command->cmd[j])
            return (free_char_array(command->cmd), command->cmd = tmp_tab, (void)0);
        i++;
        j++;
    }
    command->cmd[j] = NULL;
    free_char_array(tmp_tab);
}

void rm_void_tab_cmd(t_cmd **tab_cmd)
{
    int i;
    int num;

    if (!tab_cmd)
        return ;
    i = 0;
    while (tab_cmd[i])
    {
        num = get_tab_num(tab_cmd[i]->cmd);
        rm_void_from_cmd(tab_cmd[i], 0, 0, num);
        i++;
    }
} */