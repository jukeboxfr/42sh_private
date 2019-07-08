/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:25:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 16:53:03 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	**ft_args_tild(char **args, t_env **copy_env)
{
	int	i;

	i = 0;
	while (args[i])
	{
		args[i] = ft_args_tilde_get(args[i], copy_env);
		i++;
	}
	return (args);
}

static char	**ft_args_dollar(char **args, t_env **copy_env, int *p_res_parse)
{
	int		i;
	int		j;
	char	*tmp;
	char	*to_free;

	i = 0;
	while (args[i])
	{
		tmp = ft_args_dollar_get(args[i], copy_env, p_res_parse);
		if (tmp == NULL)
		{
			j = i - 1;
			while (args[++j])
				ft_memdel((void **)&(args[j]));
			ft_list_free(&args);
			return (NULL);
		}
		to_free = args[i];
		args[i] = tmp;
		ft_memdel((void **)&to_free);
		i++;
	}
	args[i] = 0;
	return (args);
}

char		**ft_args_get(char *cmd, t_env **copy_env, int *p_res_parse)
{
	char	**args;

	args = ft_strsplit(cmd, ' ');
	if (args == NULL || args[0] == NULL)
	{
		ft_memdel((void **)args);
		return (NULL);
	}
	args = ft_args_tild(args, copy_env);
	args = ft_args_dollar(args, copy_env, p_res_parse);
	return (args);
}
