/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:27 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/02 12:14:50 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

///////////////////////
//	    CONVERT      //
///////////////////////

/* Reads a String, and, after ignoring spaces
with ft_isspace, saves the string into an integer */
int		ft_atoi(const char *str);

/* Reads a String, and, after ignoring spaces
with ft_isspace, saves the string into an integer */
ssize_t	ft_atolli(const char *str);

/* Saves the given number as a string (char array) */
char	*ft_itoa(int n);

/* Return positiv number */
int		ft_abs(int nb);

/* Return rounded number */
int		ft_round(float num);

/* Return -1 if num < 0, 1 if > 0 and 0 if 0 */
int		ft_sign(int num);

/////////////////////
//      CHECKS     //
/////////////////////

/* Returns 1 if the input is a number or a letter in the ASCII table */
int		ft_isalnum(int ch);

/* Returns 1 if the input is a letter in the ASCII table */
int		ft_isalpha(int ch);

/* Returns whether or not a value belongs to the ASCII table */
int		ft_isascii(int ch);

/* Returns 1 if the input is a number in the ASCII table */
int		ft_isdigit(int ch);

/* Returns whether a character is printable */
int		ft_isprint(int ch);

/* Returns if complete string is numeric, ignores leading + or -*/
int		ft_is_str_num(char *str);

/* Return if string is a number and inside int min/max range */
int		ft_is_str_int(char *str);

/* Returns if char is \t \f \n \r \v or ' ' */
int		ft_is_space(const char *ch);

/////////////////////
//     MEMORY    ////
/////////////////////

/* Writes n zeroes to the string s */
void	ft_bzero(void *s, size_t size);

/* Reserves x blocks of y bits of memory */
void	*ft_calloc(size_t count, size_t size);

/* Looks for a matching character inside a part of the memory */
void	*ft_memchr(const void *s, int c, size_t n);

/* Compares two parts of memory, returning 0 if they're the same,
 * or a nonzero value */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/* Copies from one part of memory to another, ignoring possible overlaps*/
void	*ft_memcpy(void *dest, const void *src, size_t n);

/* Copies from one part of memory to another, preventing possible overlaps*/
void	*ft_memmove(void *dest, const void *src, size_t n);

/* Assigns a character n times to a part of the memory*/
void	*ft_memset(void *s, int c, size_t n);

/* Free array, must be NULLed */
void	ft_free_array(void **arr);

/* Free 2D array, must be NULLed */
void	ft_free_2darray(void ***arr);

/////////////////////
//    STRING     ////
/////////////////////

/* Looks for a specific character inside a given string,
 * returning pointer to it*/
char	*ft_strchr(const char *s, int c);

/* Returns true if both strings are equivalent */
int		ft_streq(char *s1, char *s2);

/* Saves enoug space and duplicates a string */
char	*ft_strdup(const char *s);

/* Concatenates two strings ensuring it ends with \0 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* Copies n - 1 bytes from a source string to a destination string */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/* Returns length of a string */
size_t	ft_strlen(const char *str);

/* Compares two strings up to the n-th character */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* Tries to find a substring (needle) in a second string (haystack)
 * before the n-th char is reached */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/* Looks for a given character in a string, reading it from back to front */
char	*ft_strrchr(const char *s, int c);

/* Makes every uppercase character in a string lowercase */
int		ft_tolower(int ch);

/* Makes every lowercase character in a string uppercase */
int		ft_toupper(int ch);

/* Copies from the n-th char of a string */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* Concatenates two strings allocating enough space first */
char	*ft_strjoin(char const *s1, char const *s2);

/* Concatenates n strings allocating enough space first */
char	*ft_strnjoin(size_t arg_count, ...);

/* Removes occurrences of characters in a string from the start
 * to the end of another one. Allocates memory if successful */
char	*ft_strtrim(char const *s1, char const *set);

/* Splits a string according to a given separator character.
Allocates memory if successful */
char	**ft_split(char const *s, char c);

/* Applies a function (mapping) to every element in a string */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* Prints a character to the given file descriptor */
void	ft_putchar_fd(char c, int fd);

/* Prints string to the given file descriptor */
void	ft_putstr_fd(char *s, int fd);

/* Prints a string followed by a new line \n to a given file descriptor */
void	ft_putendl_fd(char *s, int fd);

/* Prints number to the given file descriptor */
void	ft_putnbr_fd(int n, int fd);

/* Converts and prints a number with a given base */
void	ft_putnbr_base(int nbr, char *base);

/////////////////////
//     LIST      ////
/////////////////////

/* Adds new node at the beginning of the linked list */
void	ft_lstadd_front(t_list **lst, t_list *new);

/* Adds new node at the end of the linked list */
void	ft_lstadd_back(t_list **lst, t_list *new);

/* Deletes a given element and every element after that */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/* Deletes, frees, and applies function del to content of a given node */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/* Applies a function to the content of every node of the linked list */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/* Retrieves last node of the list */
t_list	*ft_lstlast(t_list *lst);

/* Applies function to a copy of the list, freeing when necessary */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Creates new node allocating with malloc */
t_list	*ft_lstnew(void *content);

/* Returns number of elements of linked list */
int		ft_lstsize(t_list *lst);

#endif
