/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:22:12 by axlee             #+#    #+#             */
/*   Updated: 2024/06/23 16:07:18 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

/*
** List Struct
** content: the data contained in the element.
** next: the next element’s address or NULL if it’s the last element
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** Bonus Functions
*/
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/*
** Aditional Functions
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
int					ft_sprintf(char *str, const char *format, ...);
void				ft_split_free(char ***str_array);
char				*ft_itoa(int n);
char				*ft_ltoa(long n);
char				*ft_dtoa(double n, int p);
float				ft_atof(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_nbr_base(long long nbr, char *base);
char				*ft_ullnbr_base(unsigned long long nbr, char *base);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
int					ft_isspace(int c);
int					add_char(char **str, char c);
void				invert_str(char *src, char **dest);

/*
** Libc Functions
*/
size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t count);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t count);
char				*ft_strchr(const char *s, int c);
int					ft_isdigit(int c);
int					ft_isnumeric(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_strdel(char **str);
void				ft_strswap(char **s1, char **s2);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *str, size_t size);
int					ft_atoi(const char *nptr);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strccmp(const char *s1, const char *s2, char c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

#endif
