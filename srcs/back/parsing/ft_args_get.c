/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:25:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/05 00:26:23 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_args_get(char *cmd, t_env **copy_env, int *p_result_parsing)
{
	char	**args;
	int		i;
	int		j;

	args = ft_strsplit(cmd, ' ');
	i = 0;	
	while (args && args[i])
	{
		args[i] = ft_args_dollar_get(args[i], copy_env, p_result_parsing);
		if (args[i] == NULL)
		{
			j = i + 1;
			while (args[j])
			{
				ft_memdel((void **)&(args[j]));
				j++;
			}
			ft_list_free(&args);
			return (NULL);
		}
		args[i] = ft_args_tilde_get(args[i], copy_env);
		args[i] = ft_strtrim_free(args[i]);
		i++;
	}
	return (args);
}