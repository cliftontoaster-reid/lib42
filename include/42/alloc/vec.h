/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:56:36 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 13:59:49 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "macros.h"

typedef struct s_vec {
  void* data;
  size_t size;
  size_t capacity;
  size_t elem_size;
} t_vec;

t_vec* vec_create(size_t elem_size);
bool vec_push_back(t_vec* vec, const void* elem);
bool vec_push_front(t_vec* vec, const void* elem);
bool vec_pop_back(t_vec* vec);
bool vec_pop_front(t_vec* vec);
void* vec_get(const t_vec* vec, size_t index);
bool vec_set(t_vec* vec, size_t index, const void* elem);
void vec_free(t_vec* vec);

FT_INT bool vec_resize(t_vec* vec, size_t new_capacity);