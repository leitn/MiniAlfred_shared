/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedubois <hedubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:10:06 by hedubois          #+#    #+#             */
/*   Updated: 2023/11/23 15:38:32 by hedubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_get_paths(t_env *en, t_bin *bin)
{
	char	*path_tmp;
	char	**paths;

	path_tmp = ft_getenv(en, "PATH");
	paths = ft_split(path_tmp, ':');
	ft_add_to_the_bin(path_tmp, STR, bin);
	if (!paths)
		return (false);
	en->paths = paths;
	return (true);
}

void *ft_memcpy(void *dest, void *src, int new_size, int old_size)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (new_size == 0 || dest == src)
		return (dest);
	if (new_size > old_size)
		new_size = old_size;
	while (new_size--)
		*d++ = *s++;
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	while (n > 0)
	{
		str[i] = '\0';
		i++;
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void *ft_realloc(void *ptr, int new_size, int old_size)
{
	void *new_ptr;

	if (!ptr)
		return (ft_calloc(new_size, 1));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(new_size, 1);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, new_size, old_size);
	free(ptr);
	return (new_ptr);
}
