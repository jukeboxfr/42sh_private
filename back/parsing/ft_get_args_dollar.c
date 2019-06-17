/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:42:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/17 17:07:04 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	ft_is_special_param(char c)
{
	if (c == '*' || c == '@' || c == '#' || c == '?'|| c == '-' || c == '$' || c == '!')
		return (1);
	return (0);
}

// static void print_n(char *str, int i, int j)
// {
// 	ft_putstr("macro : ");
// 	while (i < j)
// 	{
// 		ft_putchar(str[i]);
// 		i++;
// 	}
// 	ft_putchar('\n');
// }

static int get_expansion_length(char *str)
{
	int ret;

	ret = 1;
	if (str[ret] == '{')
	{
		ret++;
		while (str[ret] && str[ret] != '}')
		{
			if (ft_is_special_param(str[ret]) && ret != 2)
				return (-1);
			if (ft_is_special_param(str[ret]) == 0 && ft_isalnum(str[ret]) == 0 && str[ret] != '_')
				return (-1);
			ret++;
		}
		if (str[ret] == 0)
		{
			return (-1);
		}
		ret++;
	}
	else
	{
		while (str[ret] && str[ret] != '/')
		{
			if (ft_is_special_param(str[ret]))
			{
				if (ret == 1)
					ret++;
				break;
			}
			else if (ft_isalnum(str[ret]) == 0 && str[ret] != '_')
				break ;
			ret++;
		}
	}
	return (ret);
}

static char *get_expansion(char *str, int i, int j, t_env **copy_env)
{
	char *line;

	// print_n(str, i, j);

	i++;

	if (str[i] == '{')
	{
		line = ft_env_get_line_n(copy_env, str + i + 1, j - 2 - i);
		// print_n(str + i + 1, 0, j - 2 - i);
		if (line)
			return (ft_strdup(line) + j - i -1);
		else
			return (ft_strdup(""));
	}
	else
	{
		line = ft_env_get_line_n(copy_env, str + i, j - i);
		if (line)
			return (ft_strdup(line) + j - i + 1);
		else
			return (ft_strdup(""));
	}
}



char *ft_get_args_dollar(char *str, t_env **copy_env)
{
	int i;
	int j;
	int ret;

	i = 0;
	if (copy_env)
	{
	}
	while (str[i])
	{
		if (str[i] == '$')
		{
			ret = get_expansion_length(str + i);
			if (ret == -1)
			{
				ft_putstr_fd("bad substitution\n", 2);
				return (NULL);
			}
			j = ret + i;
			char *tmp;

			tmp = get_expansion(str, i, j, copy_env);
			tmp = ft_strjoin(tmp, str + j);
			str[i] = 0;
			str = ft_strjoin(str, tmp);
		}
		i += 1;
	}
	return (str);
}
