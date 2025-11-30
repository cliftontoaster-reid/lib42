/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:45:33 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 14:58:43 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/map.h"

t_map* map_create(size_t default_key_size, size_t default_value_size,
                  int (*cmp)(const void*, size_t, const void*, size_t)) {
  t_map* m = malloc(sizeof(t_map));
  if (m == NULL) {
    errno = ENOMEM;
    return NULL;
  }
  m->entries = NULL;
  m->size = 0;
  m->default_key_size = default_key_size;
  m->default_value_size = default_value_size;
  m->cmp = cmp;
  return m;
}
