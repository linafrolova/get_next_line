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

#endif
