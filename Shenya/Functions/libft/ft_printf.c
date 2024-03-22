/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:46:29 by sde-silv          #+#    #+#             */
/*   Updated: 2023/07/12 17:21:53 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len ++;
	return (len);
}
*/
static int	check_specifier(int spec, va_list ap)
{
	if (spec == 's')
		return (print_str((char *)va_arg(ap, char *)));
	else if (spec == '%')
		return (write (1, "%", 1));
	else if (spec == 'c')
		return (print_chr(va_arg(ap, int)));
	else if (spec == 'd' || spec == 'i')
		return (print_int(va_arg(ap, int)));
	else if (spec == 'p')
		return (print_ptr(va_arg(ap, unsigned long int), spec));
	else if (spec == 'x' || spec == 'X')
		return (print_hex((unsigned int)va_arg(ap, unsigned long int), spec));
	else if (spec == 'u')
		return (print_uint(va_arg(ap, unsigned int)));
	else
		return (-1);
}

#ifdef __linux__

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '%')
		{
			i++;
			ret = ret + check_specifier(str[i], ap);
		}
		else
			ret = ret + write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (ret);
}

#else

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	va_start(ap, str);
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '%')
		{
			i++;
			ret = ret + check_specifier(str[i], ap);
		}
		else
			ret = ret + write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (ret);
}

#endif