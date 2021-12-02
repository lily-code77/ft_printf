#include "ft_printf.h"

size_t ft_strlen(char *str)
{
    size_t len;

    len = 0;
    while (str[len])
        len ++;
    return (len);
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;
	size_t src_len;

    i = 0;
	src_len = ft_strlen(src);
    if (dstsize == 0)
        return (src_len);
    while (i < dstsize - 1 && src[i])
    {
        dst[i] = src[i];
        i ++;
    }
    dst[i] = '\0';
    return (src_len);
}

size_t count_num(int nb)
{
    size_t counter;

    counter = 0;
    if (nb == INT_MIN)
    {
        counter ++;//「-」分
        nb = (-1) * (INT_MIN / 10);
        counter ++;//「末尾の8」分
    }
    if (nb < 0)
    {
        counter ++;
        nb = (-1) * nb;
    }
    else if (nb == 0)
        counter ++;
    while (nb > 0)
    {   
        nb = nb / 10;
        counter ++;
    }
    return (counter);
}

char *ft_strcpy(char *dest, char *src)
{
    size_t i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i ++;
    }
    dest[i] = '\0';
    return (dest);
}

char *ft_itoa(int n)
{
    size_t amount;
    char *result;

    amount = count_num(n);
    result = (char *)malloc(sizeof(char) * (amount + 1));
    if (!result)
        return (NULL);
    if (n == 0)
		return(ft_strcpy(result, "0"));//result[0] = '0';
    if (n == INT_MIN)
        return (ft_strcpy(result, "-2147483648"));
    if (n < 0)
	{
        result[0] = '-';
		n = n * (-1);
	} 
    result[amount --] = '\0';
	while (n > 0)
	{
		result[amount] = '0' + (n % 10);
		n = n / 10;
		amount--;
	} 
    return (result);
}