/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_abs_path_cdpath.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 21:58:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 21:31:23 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_cd_get_abs_path_cdpath(t_env ***p_environ, char *element, int fds[], char *cd_path)
{
	char **list;
    char *dest_path;
	int i;
	
	(void)p_environ;
	list = ft_str_separate(cd_path, ':');
	if (ft_strlen(list[0]) == 0)
	{
		dest_path = ft_strjoin("./", element);
		if (ft_cd_can_go_to(dest_path) == 1)
		{
			ft_list_free(&list);
			return (dest_path);
		}
		ft_memdel((void **)&dest_path);
	}
	i = 0;
	while (list && list[i])
	{
		if (ft_strlen(list[i]) == 0)
		{
			i++;
			continue ;
		}
		dest_path = ft_strjoin_(list[i], "/", element);
		if (ft_cd_can_go_to(dest_path) == 1)
		{
			ft_dprintf(fds[1], "%s\n", dest_path);
			ft_list_free(&list);
			return (dest_path);
		}
		ft_memdel((void **)&dest_path);
		i++;
	}
	ft_list_free(&list);
	return (NULL);
}