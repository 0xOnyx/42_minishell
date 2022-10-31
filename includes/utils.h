#ifndef UTILS_H
# define UTILS_H
# include "includers.h"

int		ft_memset(void *dst, int c, size_t n);
int		ft_memcpy(void *src, void *dst, size_t len);
int		ft_strdup(char **dst, char *src);
size_t 	ft_putstr_fd(char *str, int fd);

int 	ft_strncmp(char	*a, char *b, size_t n);
size_t	ft_strlen(const char *str);
int		is_in_charset(char c, const char *charset);

#endif