/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_deep_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:08:11 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 16:29:12 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env **ft_env_deep_copy(t_env **cp_env)
{
    t_env **copy;
    int i;

    i = 0;
    while (cp_env[i])
        i++;
    if (!(copy = (t_env **)ft_memalloc((i + 1) * sizeof(t_env *))))
		return (NULL);
    i = 0;
    while (cp_env[i])
    {
        copy[i] = ft_memalloc(sizeof(t_env));
		copy[i] = (t_env *)ft_memcpy(copy[i], (void *)cp_env[i], sizeof(t_env));
        i++;
    }
    copy[i] = 0;
    return (copy);
}