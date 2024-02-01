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
    char *content;
    struct s_buffer *next;
} t_buffer;

char	    *ft_strdup(const char *s);
int         found_newline(t_buffer *list);
int	        len_to_newline(t_buffer *list);
void	    copy_str(t_buffer *list, char *str);
void        create_list(t_buffer **list, int fd);
char	    *fetch_line(t_buffer *list);
void        extract_content(char *src, char **dest);
void        deallocate_list(t_buffer **list, t_buffer *last_node);
char        *get_next_line(int fd);
void        append_node(t_buffer **head, const char *str_buf);

#endif
