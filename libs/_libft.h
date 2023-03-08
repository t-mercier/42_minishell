/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _libft.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:09:47 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/02 13:44:38 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct s_vector
{
	void				*data;
	size_t				len;
	size_t				cap;
	size_t				esz;
}						t_vector;

typedef int				(*t_f_compare)(void *a, void *b);

static inline size_t	min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

/*					ft_alloc.c
** ------------------------------------------ */
void					*ft_malloc(size_t n);
void					*ft_calloc(size_t nmemb, size_t size);

/*					ft_is1.c
** ------------------------------------------ */
int						ft_isdigit(int c);
int						ft_islower(int c);
int						ft_isupper(int c);
int						ft_isalpha(int c);
int						ft_isalnum(int c);

/*					ft_is2.c
** ------------------------------------------ */
int						ft_isprint(int c);
int						ft_isascii(int c);
int						ft_isspace(int c);

/*					ft_list1.c
** ------------------------------------------ */
t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);

/*					ft_list2.c
** ------------------------------------------ */
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
/*					ft_mem.c
** ------------------------------------------ */
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t n);
void					*ft_memset(void *s, int c, size_t n);
void					*ft_memchr(void *s, int c, size_t n);
int						ft_memcmp(void *s1, void *s2, size_t n);

/*					ft_put.c.c
** ------------------------------------------ */
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);

/*					ft_str1.c
** ------------------------------------------ */
char					*ft_strnstr(char *big, char *little, size_t len);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(char *s1, char *s2, size_t n);
int						ft_strcmp(char const *s1, char const *s2);

/*					ft_str2.c
** ------------------------------------------ */
char					*ft_strdup(char *s);
char					*ft_strndup(char *s, size_t n);
size_t					ft_strlcpy(char *dst, const char *src, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t n);
char					*ft_strjoin(char const *s1, char const *s2);

/*					ft_str3.c
** ------------------------------------------ */
char					*ft_strtrim(char const *s1, char const *set);
char					**ft_split(char const *s, char c);

/*					ft_str4.c
** ------------------------------------------ */
size_t					ft_strlen(const char *s);
size_t					ft_strnlen(const char *s, size_t n);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));

/*					ft_to.c
** ------------------------------------------ */
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_atoi(const char *nptr);
char					*ft_itoa(int n);

/*					ft_misc.c
** ------------------------------------------ */
void					ft_bzero(void *s, size_t n);

/*					v1.c
** ------------------------------------------ */

t_vector				*ft_vector_create(size_t esz);
void					ft_vector_grow(t_vector *v, size_t n);
void					*ft_realloc(void *d, size_t n, size_t old_s);

/*					v2.c
** ------------------------------------------ */
void					*ft_vector_push(t_vector *v, void *el);
void					*ft_vector_pop(t_vector *v);
void					ft_vector_swap(t_vector *v, int a, int b);
void					*ft_vector_get(t_vector *v, int i);
t_vector				*ft_vector_copy(t_vector *v);

/*					v3.c
** ------------------------------------------ */
ssize_t					ft_vector_indexof(t_vector *v, void *e,
							t_f_compare cmp);
void					ft_vector_destroy(t_vector *v);
void					ft_vector_concat(t_vector *v, void *d, size_t n);
t_vector				*ft_vec_concat_str(t_vector *v, char *s);
void					*ft_vector_set(t_vector *v, size_t i, void *el);

void					*ft_vector_delfast(t_vector *v, size_t i);

/*					get_next_line.c
** ------------------------------------------ */
char					*get_next_line(int fd);

/*					get_next_line_utils.c
** ------------------------------------------ */
void					*_gnl_memcpy(void *dst, void *src, size_t n);
size_t					_gnl_strlen(const char *s);
void					*_gnl_fake_realloc(void *p, size_t on, size_t n);

#endif // _LIBFT_H
