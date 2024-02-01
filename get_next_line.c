/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrolova <lfrolova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:00:07 by lfrolova          #+#    #+#             */
/*   Updated: 2024/01/09 14:00:08 by lfrolova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

void create_list(t_buffer **list, int fd)
 {
    int char_read;
    char *buf;

    while (!found_newline(*list)) 
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return ;
        char_read = read(fd, buf, BUFFER_SIZE);
        if (char_read <= 0) 
        {
            free(buf);
            return ;
        }
        buf[char_read] = '\0';
        append_node(list, buf);
        free (buf);
    }
}

char	*fetch_line(t_buffer *list)
{
	int		str_len;
	char	*next_str;

    if (list == NULL)
    {
        return (NULL);
    }
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void extract_content(char *src, char **dest) 
{
    char *buf;
    int i;
    int k;
    
    buf = malloc(BUFFER_SIZE + 1);
    if (buf == NULL)
        return ;
    i = 0; 
    k = 0;
    while (src[i] && src[i] != '\n')
        ++i;
    while (src[i] && src[++i])
        buf[k++] = src[i];
    buf[k] = '\0';
    *dest = buf;
}

void deallocate_list(t_buffer **list, t_buffer *last_node) 
{
    char *buf;
    t_buffer *clean_node;
    t_buffer *tmp;

    extract_content(last_node->content, &buf);
    clean_node = malloc(sizeof(t_buffer));
    if (clean_node == NULL)
        return ;
    clean_node->content = buf;
    clean_node->next = NULL;
    while (*list) 
    {
        tmp = (*list)->next;
        free((*list)->content);
        free(*list);
        *list = tmp;
    }
    *list = NULL;
    if (clean_node->content[0])
        *list = clean_node;
    else 
    {
        free(buf);
        free(clean_node);
    }
}

char *get_next_line(int fd)
{
    static t_buffer *list = NULL;
    char *next_line;
    t_buffer *last_node;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
        return (NULL);
    create_list(&list, fd);
    if (list == NULL)
        return NULL;
    last_node = list;
    while (last_node->next)
		last_node = last_node->next;
    next_line = fetch_line(list);
    deallocate_list(&list, last_node);
    return (next_line);
}