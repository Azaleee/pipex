/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:59:06 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/26 19:23:40 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	strcmp is a function that compares 
	two strings, but with a size limit
*/

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	if (s2 == NULL || s1 == NULL)
		return (-1);
	while (n)
	{
		if (*s1 != *s2 || *s1 == '\0')
			return ((int)(*s1 - *s2));
		s1++;
		s2++;
		n--;
	}
	return (0);
}
