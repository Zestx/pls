/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:04:33 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/12 18:09:37 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_printab(char **tab)
{
	char **roam;

	if (!tab)
		return ;
	roam = tab;
	while (*roam)
	{
		printf("arg: [%s]\n", *roam);
		roam++;
	}
}
