/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_abs_path_cdpath.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 21:58:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 22:04:02 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_cd_get_abs_path_cdpath(t_env ***p_environ, char *element, int fds[], char *cd_path)
{
	char **list;
    char *dest_path;

		list = ft_str_separate(cd_path, ':');

		if (ft_strlen(list[0]) == 0)
		{
			dest_path = ft_cd_get_pwd_plus_element(p_environ, element);
			if (ft_cd_can_go_to(dest_path) == 1)
			{
				ft_list_free(&list);
				return (dest_path);
			}
			ft_memdel((void **)&dest_path);
		}

		int i;

		i = 0;
		while (list && list[i])
		{
			if (ft_strlen(list[i]) == 0)
			{
				i++;
				continue ;
			}
			dest_path = ft_strjoin_(list[i], "/", element);
			dest_path = ft_path_trim_free(dest_path);
			if (ft_cd_can_go_to(dest_path) == 1)
			{
				if (ft_strncmp("/", list[i], 1) == 0)
				{
					ft_dprintf(fds[1], "%s\n", dest_path);
				}
				else
				{
					char *to_free;

					to_free = dest_path;
					dest_path = ft_cd_get_pwd_plus_element(p_environ, to_free);
					ft_memdel((void **)&to_free);
					ft_dprintf(fds[1], "%s\n", dest_path);
				}
				ft_list_free(&list);
				return (dest_path);
			}
			ft_memdel((void **)&dest_path);
			i++;
		}
		ft_list_free(&list);
		return (NULL);
}