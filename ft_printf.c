#include "ft_printf.h"
//★戻り値の型や変数の型は要検討。現在、ssize_tやsize_tを使用しているが、本家の返り値の型がintである以上、intの方が良いのかも。

char	*ft_convert_base(size_t nbr, char *base)//★これだと、testerでセグフォ。nbrにはunsined longとunsigned intの両方が考えられる。
{
	size_t	base_num;
	size_t	i;
	char	*nbr_c;

    nbr_c = NULL;
	base_num = ft_strlen(base);
	i = count_num(nbr);
	nbr_c[i --] = '\0';
	while (nbr > 0)
	{
		nbr_c[i] = base[nbr % base_num];
		nbr /= base_num;
		i --;
		if (i == 0)
			break ;
	}
	return (nbr_c);
}

ssize_t  conv_type(va_list ap, char input)
{
    if (input == 'c')
        return(put_c(va_arg(ap, int)));
    else if (input == 's')
        return(put_s(va_arg(ap, char*)));
    else if (input == 'p')//void*型の実引数に対して、そのメモリアドレスを表現する形。ヌルポインタでも問題ない。
        return(put_p(va_arg(ap, unsigned long)));
    else if (input == 'd' || input == 'i')//10進整数
        return(put_di(va_arg(ap, int)));
    else if (input == 'u')//符号なし10進整数
        return(put_xu(va_arg(ap, unsigned int), "0123456789"));
    else if (input == 'x')//符号なし16進整数。a-fは小文字に変換する。
        return(put_xu(va_arg(ap, unsigned int), "0123456789abcdef"));
    else if (input == 'X')//符号なし16進整数。a-fは大文字に変換する。
        return(put_xu(va_arg(ap, unsigned int), "0123456789ABCDEF"));
    else if (input == '%')//
        return(write(1, "%", 1));
    else
        return(0);
}

ssize_t  count_char(va_list ap, char *input)
{
    size_t  len;
    size_t  i;
    ssize_t  res_conv;
    ssize_t  res;

    len = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == '%')//★％の次が\0の時の対応は？lenがINT_MAXより大きい場合はreturn(-1)でアーリーリターンした方が良いかも
        {
            i ++;//'%'分
            res_conv = conv_type(ap, input[i]);//★conv_typeがエラーで返ってきた時の対応必要。各変換指定子に書き込まれた文字数を戻り値とする関数（conv_type）
            if (res_conv < 0)
                return (-1);
            len += res_conv;
        }
        else
        {
            res = write(1, &input[i], 1);
            if (res < 0)
                return(-1);
            len += res;
        }
        i ++;
    }
    return (len);
}

int	ft_printf(const char *input, ...)//戻：正常に終了した場合は、出力した文字数が返される。エラー発生時は負数が返される。
{
    va_list ap;
    int len;

    if (input == NULL)
        return(-1);//★エラー時は負の数とのことだが、何の負の数でも良いのか確認必要。
    va_start(ap, input);//apの中に、引数が全部格納される。
    len = (int)count_char(ap, (char *)input);
    va_end(ap);
    return(len);
}