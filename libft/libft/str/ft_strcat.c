#include "libft.h"

char    *ft_strcat(char *dst, const char *src)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(dst[i])
        dst[i++];
    while(src[j])
        dst[i++] = src[j++];
    dst[i] = '\0';
    return (dst);
}