/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrolova <lfrolova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:00:14 by lfrolova          #+#    #+#             */
/*   Updated: 2024/01/09 14:00:17 by lfrolova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16
#endif


# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_buffer
{
    char *data;
    struct s_buffer *next;
} t_buffer;

char	    *ft_strdup(const char *s);
char	    *ft_strchr(const char *s, int c);
char	    *find_last_node(t_buffer *list);
int	        len_to_newline(t_buffer *list);
void	    copy_str(t_buffer *list, char *str);
void	    append_node(t_buffer **head, const char *str_buf);
void        create_list(t_buffer **list, int fd);
char	    *get_line(t_buffer *list);
t_buffer    *deallocate_list(t_buffer **list, char *last_node);
char        *get_next_line(int fd);

#endif
