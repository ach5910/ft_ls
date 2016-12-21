/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_wild.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 22:14:53 by ahunt             #+#    #+#             */
/*   Updated: 2016/12/20 22:15:20 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printf_wild(va_list *ap, t_fmt **args)
{
	int nbr;

	nbr = va_arg(*ap, int);
	if ((*args)->has_percision)
		(*args)->min_width = nbr;
	else
		(*args)->width = nbr;
}