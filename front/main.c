/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:56:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 15:13:45 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


int main(int argc, char **argv)
{
    t_env **copy_env;
    int success;

    success = 0;
    if (!(copy_env = ft_env_copy_raw((char **)environ, argv)))
	{
		ft_putstr_fd("Failed to copy env\n", 2);
		return (0);
	}
    if (argc > 1 || ft_isatty(0) == 0)
		success = shell_file(&copy_env, argv);
    else
		success = shell_terminal(&copy_env);
	ft_env_free(&copy_env);
    return (success);
}