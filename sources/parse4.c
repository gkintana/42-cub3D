/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:02:00 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	ft_rgb(char *str, int i)
{
	char	*ret;
	char	**temp2;

	ret = ft_rgb1(str, i);
	if (!ret)
		return (1);
	temp2 = ft_split(ret, ',');
	free (ret);
	if (ft_array_len(temp2) != 3)
	{
		free_2d_array(temp2);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		if (!(ft_atoi2(temp2[i]) >= 0 && ft_atoi2(temp2[i]) <= 255))
		{
			free_2d_array(temp2);
			return (1);
		}
		i++;
	}
	free_2d_array(temp2);
	return (0);
}

char	*ft_rgb1(char *str, int i)
{
	char	*temp;
	char	*ret;
	int		j;

	temp = (char *)malloc(sizeof(char) * 4097);
	if (!temp)
		return (NULL);
	ft_memset(temp, '\0', 4097);
	j = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	ret = ft_rgb2(temp);
	return (ret);
}

char	*ft_rgb2(char *temp)
{
	char	*ret;
	int		j;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(temp) + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (temp[j] != '\0')
	{
		ret[j] = temp[j];
		j++;
	}
	ret[j] = '\0';
	free (temp);
	return (ret);
}
