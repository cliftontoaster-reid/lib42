/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_cstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:35:13 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 13:35:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "42/alloc/map.int.h"
#include "42/memory/cstr.h"

void* map_get_cstr(t_map* m, const char* key_cstr, size_t* out_value_size) {
  if (m == NULL || key_cstr == NULL) {
    if (out_value_size != NULL) *out_value_size = 0;
    errno = EINVAL;
    return NULL;
  }

  size_t key_size = ft_strlen(key_cstr) + 1; /* include null terminator */

  return map_get(m, key_cstr, key_size, out_value_size);
}
