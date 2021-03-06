#include "ft_printf.h"

ssize_t	put_c(int c)
{
	return (write(1, &c, 1));
}

ssize_t	put_s(char *s)
{
	if (!s)
		s = "(null)";
	return (write(1, s, ft_strlen(s)));
}

ssize_t put_p(unsigned long p)
{
	char	*str;
	ssize_t	len;

    len = write(1, "0x", 2);
	if (len < 0)
		return (-1);
    str = ft_convert_base(p, "0123456789abcdef");
	if (str == NULL)//
		return (-1);//
	len += write(1, str, ft_strlen(str));
	free(str);
    return (len);
}

ssize_t put_di(int d)
{
    char    *str;
	ssize_t	len;

    str = ft_itoa(d);
	if (str == NULL)
		return (-1);
	len = write(1, str, ft_strlen(str));
	free(str);
    return(len);
}

ssize_t	put_xu(unsigned int x, char *base)
{
	char	*str;
	int		len;

	str = ft_convert_base(x, base);
	if (str == NULL)//
		return (-1);//
	len = write(1, str, ft_strlen(str));
	free(str);
	return (len);
}
