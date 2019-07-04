/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_copy_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:05:15 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 17:17:28 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env **ft_env_copy_exit(t_env **env)
{
	ft_putstr_fd(FAIL_COPY_ENV, STDERR_FILENO);
	ft_env_free(&env);
	return (NULL);
}


t_env **ft_env_add_default_pwd(t_env **copy)
{
	char *cwd;
	int i;

	i = 0;
	cwd = (char *)ft_vars_get_value(KEY_CWD);
	while (copy[i])
		i++;
	if (!(copy[i] = ft_memalloc(sizeof(t_env))))
		return (ft_env_copy_exit(copy));
	copy[i]->line = ft_strjoin_free_second("PWD=", cwd);
	i++;
	copy[i] = 0;
	return (copy);
}

t_env **ft_env_add_default_shlvl(t_env **copy)
{
	int i;

	i = 0;
	while (copy[i])
		i++;
	if (!(copy[i] = ft_memalloc(sizeof(t_env))))
		return (ft_env_copy_exit(copy));
	copy[i]->line = ft_strdup("SHLVL=0");
	i++;
	copy[i] = 0;
	return (copy);
}

t_env **ft_env_increment_shlvl(t_env **copy)
{
	int i;
	int nb;

	i = 0;
	while (copy[i])
	{
		if (ft_env_cmp_prefix("SHLVL", copy[i]->line) == 0)
			break ;
		i++;
	}
	nb = ft_atoi(copy[i]->line + 6) + 1;
	if (nb < 0)
		nb = 0;
	else if (nb >= 1000)
	{
		ft_dprintf(STDERR_FILENO, "shell: shell level (%d) too high, resetting to 1\n", nb);
		nb = 1;
	}
	copy[i]->line = ft_strjoin_free_second("SHLVL=", ft_itoa(nb));
	return (copy);
}