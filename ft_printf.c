#include "ft_printf.h"

char	*ft_convert_base(size_t nbr, char *base)//base_numと演算する時の見た目の自然さ的に第一引数をsize_t型にした。
{
    size_t	base_num;
	size_t	digit;
    size_t  tmp;
	char	*nbr_c;
    
    base_num = ft_strlen(base);
    digit = 0;
    tmp = nbr;
    if (nbr == 0)
        digit = 1;
    while (tmp != 0)
    {
        tmp /= base_num;
        digit ++;
    }
    nbr_c = (char *)malloc(sizeof(*base) * (digit + 1));
    if (!nbr_c)
        return (NULL);
    nbr_c[digit] = '\0';
    while (digit --)
    {
        nbr_c[digit] = base[nbr % base_num];
        nbr /= base_num; 
    }
    return (nbr_c);
}

ssize_t  conv_type(va_list ap, char input)
{
    if (input == 'c')
        return(put_c(va_arg(ap, int)));
    else if (input == 's')
        return(put_s(va_arg(ap, char*)));
    else if (input == 'p')
        return(put_p(va_arg(ap, unsigned long)));
    else if (input == 'd' || input == 'i')
        return(put_di(va_arg(ap, int)));
    else if (input == 'u')
        return(put_xu(va_arg(ap, unsigned int), "0123456789"));
    else if (input == 'x')
        return(put_xu(va_arg(ap, unsigned int), "0123456789abcdef"));
    else if (input == 'X')
        return(put_xu(va_arg(ap, unsigned int), "0123456789ABCDEF"));
    else if (input == '%')
        return(write(1, "%", 1));
    else
        return(0);
}

ssize_t  count_char(va_list ap, char *input)
{
	t_counter	counter;

    counter = (t_counter){0};//
    while (input[counter.i])
    {
        if (input[counter.i] == '%')
        {
            counter.i ++;
            if (input[counter.i] == '\0')//
                break ;//
            counter.res_conv = conv_type(ap, input[counter.i]);
            if (counter.res_conv < 0 || counter.len + counter.res_conv >= INT_MAX)//
                return (-1);
            counter.len += counter.res_conv;
        }
        else
        {
            counter.res = write(1, &input[counter.i], 1);
            if (counter.res < 0 || counter.len + counter.res >= INT_MAX)//
                return(-1);
            counter.len += counter.res;
        }
        counter.i ++;
    }
    return (counter.len);
}

int	ft_printf(const char *input, ...)
{
    va_list ap;
    int len;

    if (input == NULL)
        return(-1);
    va_start(ap, input);
    len = (int)count_char(ap, (char *)input);
    va_end(ap);
    return(len);
}