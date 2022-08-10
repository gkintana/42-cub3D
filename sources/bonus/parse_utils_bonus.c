/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:26 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

int	ft_array_len(char **array)
{
	int	ret;

	ret = 0;
	if (array)
	{
		while (array[ret] != NULL)
			ret++;
	}
	return (ret);
}

//returns -1 if error
int	ft_atoi2(const char *str)
{
	int		i;
	size_t	num;

	i = 0;
	num = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (-1);
		num = (num * 10) + (str[i++] - 48);
	}
	if (num > INT32_MAX)
		return (-1);
	else
		return (num);
}
