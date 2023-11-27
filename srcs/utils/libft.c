/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 23:02:52 by letnitan          #+#    #+#             */
/*   Updated: 2023/11/27 23:04:10 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_is_eof(char *eof, char *str)
{
	while (*str)
	{
		if (*str == *eof)
		{
			str++;
			eof++;
		}
		else
			return (false);
	}
	return (!*eof);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char				*str;
	size_t				lentotal;
	int					i;
	int					j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lentotal = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc(sizeof(char) * (lentotal + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && i <= ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && j <= ft_strlen(s2))
		str[i++] = s2[j++];
	str[lentotal] = '\0';
	return (str);
}

size_t	ft_countchar(int n)
{
	size_t			i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	if (n < 0)
	{
		nb = n * (-1);
		i++;
	}
	else
		nb = n;
	while (nb != 0 || i == 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n, t_shell *shell)
{
	size_t			i;
	size_t			j;
	char			*str;
	long			nb;

	i = ft_countchar(n);
	nb = n;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_add_to_the_bin(str, STR, shell->bin);
	j = 0;
	if (n < 0)
	{
		str[j++] = '-';
		nb = nb * (-1);
	}
	str[i] = '\0';
	while (i > j)
	{
		str[--i] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}
