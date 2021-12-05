#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_counter
{
    size_t  len;
    size_t  i;
    ssize_t  res_c;//
    ssize_t  res; 
}	t_counter;

int		ft_printf(const char	*format, ...);
int	ft_vprintf(char *input, va_list ap);
ssize_t  conv_type(char input, va_list ap);
char	*ft_convert_base(size_t n, char *base);
ssize_t	put_c(int c);
ssize_t	put_s(char *s);
ssize_t	put_p(unsigned long p);
ssize_t	put_di(int d);
ssize_t	put_xu(unsigned int x, char *base);
size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t 	count_num(int nb);
char	*ft_strcpy(char *dest, char *src);
char	*ft_itoa(int n);

#endif