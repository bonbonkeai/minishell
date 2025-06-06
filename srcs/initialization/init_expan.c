#include "minishell.h"

// int	init_expansion(t_expansion *exp)
// {
// 	if (!exp)
// 		return (0);
// 	ft_bzero(exp, sizeof(t_expansion));
// 	exp->str = NULL;
// 	exp->buf = malloc(INIT_SIZE);
// 	exp->result = malloc(INIT_SIZE);
// 	if (!exp->buf || !exp->result)
// 	{
// 		free(exp->buf);
// 		free(exp->result);
// 		return (0);
// 	}
// 	exp->buf[0] = '\0';
// 	exp->result[0] = '\0';
// 	exp->size = INIT_SIZE;
// 	exp->len = 0;
// 	exp->i = 0;
// 	exp->k = 0;
// 	exp->in_squote = 0;
// 	exp->in_dquote = 0;
// 	exp->exit_status = NULL;
// 	exp->env_val = NULL;
// 	return (1);
// }

int init_expand(t_expansion *exp)
{
    if (!exp)
        return (0);
    ft_bzero(exp, sizeof(t_expansion));
    exp->str = NULL;
    exp->buf = malloc(INIT_SIZE);
    if (!exp->buf)
        return (0);
    exp->buf[0] = '\0';
    exp->size = INIT_SIZE;
    exp->len = 0;
    exp->i = 0;
    exp->in_squote = 0;
    exp->in_dquote = 0;
    exp->exit_status = NULL;
    exp->env_val = NULL;
    exp->var_name = NULL;
    exp->illegal_type = 0;
    exp->error_char = NULL;
    return (1);
}

int get_tab_num(char **tab)
{
    int i;
    
    i = 0;
    if (!tab)
        return (0);
    while (tab[i])
        i++;
    return (i);
}

void	free_expansion(t_expansion *exp)
{
	if (!exp)
		return ;
	free(exp->buf);
	free(exp->str);
	free(exp->exit_status);
	free(exp->env_val);
}

// void rm_void_from_cmd(t_cmd *command, int i, int j, int num)
// {
//     char **tmp_tab;
//     char **new_cmd;

//     tmp_tab = command->cmd;
//     while (tmp_tab[i])
//     {
//         if (!strcmp("", tmp_tab[i]))
//             i++;
//         else
//             break;
//     }
//     if (i == num)
//         return;
//     new_cmd = malloc((num - i + 1) * sizeof(char *));
//     if (!new_cmd)
//     {
//         command->cmd = tmp_tab;
//         return;
//     }
//     while (tmp_tab[i])
//     {
//         new_cmd[j] = ft_strdup(tmp_tab[i]);
//         if (!new_cmd[j])
//         {
//             free_paths(new_cmd);
//             command->cmd = tmp_tab;
//             return;
//         }
//         i++;
//         j++;
//     }
//     new_cmd[j] = NULL;
//     free_paths(tmp_tab);
//     command->cmd = new_cmd;
// }

// void rm_void_tab_cmd(t_cmd **tab_cmd)
// {
//     int i;
//     int num;

//     if (!tab_cmd)
//         return;
//     i = 0;
//     while (tab_cmd[i])
//     {
//         num = get_tab_num(tab_cmd[i]->cmd);
//         rm_void_from_cmd(tab_cmd[i], 0, 0, num);
//         i++;
//     }
// }


// void rm_void_from_cmd(t_cmd *command, int i, int j, int num)
// {
//     char **tmp_tab;

//     tmp_tab = command->cmd;
//     while (command->cmd[i])
//     {
//         if (!strcmp("", command->cmd[i]))
//             i++;
//         else
//             break;
//     }
//     if (i == num)
//         return ;
//     command->cmd = malloc((num - i + 1) * sizeof(char *));
//     if (!command->cmd)
//         return (command->cmd = tmp_tab, (void)0);
//     while (tmp_tab[i])
//     {
//         command->cmd[j] = ft_strdup(tmp_tab[i]);
//         if (!command->cmd[j])
//             return (free_char_array(command->cmd), command->cmd = tmp_tab, (void)0);
//         i++;
//         j++;
//     }
//     command->cmd[j] = NULL;
//     free_char_array(tmp_tab);
// }

// void rm_void_tab_cmd(t_cmd **tab_cmd)
// {
//     int i;
//     int num;

//     if (!tab_cmd)
//         return ;
//     i = 0;
//     while (tab_cmd[i])
//     {
//         num = get_tab_num(tab_cmd[i]->cmd);
//         rm_void_from_cmd(tab_cmd[i], 0, 0, num);
//         i++;
//     }
// }