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

// char	*ft_strchr(const char *s, int c)
// {
// 	char	*str;
// 	int		n;
// 	int		i;

// 	str = (char *)s;
// 	if (!c)
// 		return (str + ft_strlen(str));
// 	n = ft_strlen(str);
// 	i = 0;
// 	while (i < n)
// 	{
// 		if (str[i] == (char)c)
// 			return (str + i);
// 		i++;
// 	}
// 	return (0);
// }

// void	ft_bzero2(int *array, int len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		array[i] = 0;
// 		i++;
// 	}
// }

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
