/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:20:01 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 16:20:01 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>

#include "42/alloc/string.h"

/**
 * @brief Allocate and initialize a new empty string.
 *
 * Creates a t_string with an empty buffer, size 0 and an initial capacity
 * suitable for subsequent appends.
 *
 * @return Pointer to a newly allocated t_string on success, or NULL if
 *         allocation fails.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          string_free to avoid a memory leak.
 */
t_string* string_new() {
  t_string* s = (t_string*)malloc(sizeof(t_string));
  if (!s) return NULL;

  s->magic = STRING_MAGIC;
  s->size = 0;
  s->capacity = 0;
  s->data = NULL;

  return s;
}
