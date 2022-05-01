/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 19:12:53 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/21 21:44:22 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(char *src, int size)
{
	char	*result;
	char	*tmp;
	int		i;

	result = (char*)malloc(size + 1);
	tmp = result;
	i = 0;
	while (i < size)
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (result);
}

static int	get_word_n(char *str, char set)
{
	int n;

	n = 0;
	while (*str != '\0')
	{
		if (*str == set)
			n++;
		str++;
	}
	return (n + 2);
}

char		**ft_split(char const *str, char set)
{
	char	**arr;
	char	*tmp;
	int		len;
	int		i;
	int		ii;

	arr = (char**)malloc(sizeof(char*) * get_word_n((char*)str, set));
	i = 0;
	ii = 0;
	while (ii < (int)ft_strlen(str))
	{
		if (str[ii] != set && (len = 0) + 1)
		{
			tmp = (char*)str + ii;
			while (str[ii] != '\0' && (len++ + 1))
				if (str[++ii] == set)
					break ;
			arr[i++] = ft_strndup(tmp, len);
		}
		ii++;
	}
	arr[i] = NULL;
	return (arr);
}
