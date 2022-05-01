/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 09:27:00 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/22 10:24:06 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr_sub(int n, int fd)
{
	char	buf[12];
	int		i;

	i = 0;
	while (n != 0)
	{
		buf[i] = n % 10 + '0';
		i++;
		n /= 10;
	}
	while (i > 0)
	{
		i--;
		write(fd, &buf[i], 1);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < -0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	putnbr_sub(n, fd);
}
