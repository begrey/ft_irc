/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:22:23 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/23 21:35:49 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;

	if (*little == '\0')
		return ((char*)big);
	if (ft_strlen(big) < ft_strlen(little) || len < ft_strlen(little))
		return (NULL);
	i = 0;
	while (i <= len - ft_strlen(little) && big[i])
	{
		if (ft_memcmp(big + i, little, ft_strlen(little)) == 0)
			return ((char*)big + i);
		i++;
	}
	return (NULL);
}
