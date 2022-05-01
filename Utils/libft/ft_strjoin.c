/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:34:56 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/21 17:38:03 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *result;
	char *tmp;

	result = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	tmp = result;
	while (*s1 != '\0')
		*(tmp++) = *(s1++);
	while (*s2 != '\0')
		*(tmp++) = *(s2++);
	*tmp = '\0';
	return (result);
}
