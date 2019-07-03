/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 23:41:42 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/*
** Read one line of stdin (it can be better to change linked list to double)
*/

static t_cmd *ft_cmd_init(t_env **copy_env)
{
	t_cmd *cmd;

	cmd = (t_cmd *)ft_memalloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->head = ft_lstnew(0, 0);
	cmd->size = 0;
	cmd->len = 0;
	cmd->last_key = 0;
	cmd->copy_env = copy_env;
	return (cmd);
}

int ft_terminal_get_cmd(char **command, t_env **copy_env)
{	
    int ret;
	t_list *head;
	char *join;
	t_cmd *cmd;

	cmd = ft_cmd_init(copy_env);
	head = cmd->head;
	while (42)
	{
		ret = ft_terminal_read_key();
		cmd->last_key = ret;
		ret = ft_apply_key(cmd, 1);
		if (ret == 0)
			break ;
	}
	ft_putstr_fd("\n\r", STDIN_FILENO);
	join = ft_node_join(cmd->head, cmd->size);
	*command = ft_strrchr(join, '\n');
	if (*command == NULL)
		*command = ft_strdup(join);
	else
		*command = ft_strdup(ft_strrchr(join, '\n'));
	ft_memdel((void **)&join);
	ft_lstfree(cmd->head);
	ft_memdel((void **)&cmd);
    return (ret);
}

int ft_stdin_get_cmd(int fd, char **command, t_env **copy_env)
{	
    char ret;
	t_list *head;
	t_list *node;
	char *join;
	t_cmd *cmd;

	cmd = ft_cmd_init(copy_env);
	head = cmd->head;
	while (42)
	{
		if ((read(fd, &ret, sizeof(char)) == 0))
		{
			*((int *)ft_vars_get_value(KEY_MUST_EXIT)) = 1;
			break ;
		}
		cmd->last_key = (int)ret;
		if (ret == '\n' || ret == '\0')
		{
			break ;
		}
		node = ft_lstnew((void *)&(cmd->last_key), sizeof(int));
		ft_lstinsert(&head, node);
		cmd->size = cmd->size + 1;
		cmd->len = cmd->len + 1;
	}
	join = ft_node_join(cmd->head, cmd->size);
	// *command = ft_strrchr(join, '\n');
	// if (*command == NULL)
	// {
	// 	*command = join;
	// 	ft_lstfree(head);
	// 	ft_memdel((void **)&cmd);
	// 	return (ret);
	// }
	*command = join;
	// ft_memdel((void **)&join);
	ft_lstfree(head);
	ft_memdel((void **)&cmd);
    return (ret);
}