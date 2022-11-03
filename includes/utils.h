#ifndef UTILS_H
# define UTILS_H
# include "includers.h"

int 	ft_bzero(void *dst, size_t size);
int		ft_memset(void *dst, int c, size_t n);
int		ft_memcpy(void *dst, void *src, size_t len);
int		ft_strdup(char **dst, char *src);
size_t 	ft_putstr_fd(char *str, int fd);

int 	ft_strncmp(char	*a, char *b, size_t n);
int		is_in_charset(char c, const char *charset);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, char *src, size_t size);
int 	ft_strjoin(char **buff, char *a, char *b);
int		ft_split(char ***split, char *s, char c);
void 	free_split(char **element);

#endif