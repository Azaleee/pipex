/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:57:56 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/23 13:49:51 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	strdup function is used to create a copy of a string. 
	It dynamically allocates memory for this copy and returns a pointer 
	to this memory
*/

char	*ft_strdup(const char *s)
{
	int		i;
	char	*final;

	final = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!final)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		final[i] = s[i];
		i++;
	}
	final[i] = '\0';
	return ((char *)final);
}
