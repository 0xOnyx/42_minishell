/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:31:13 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:31:16 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_command	t_command;
typedef struct s_lexical	t_lexical;
typedef struct s_data		t_data;
typedef struct s_malloc		t_malloc;
typedef struct s_lexical	t_lexical;

t_data	*get_data(t_data *new_ptr);

#endif
