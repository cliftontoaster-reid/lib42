/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set_cstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:29:08 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 13:33:41 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/map.int.h"
#include "42/memory/cstr.h"
#include "42/memory/ops.h"

int map_set_cstr(t_map* m, const char* key_cstr, const void* value,
                 size_t value_size, int owned_flags, void (*del_value)(void*)) {
  if (m == NULL || key_cstr == NULL) {
    errno = EINVAL;
    return false;
  }

  size_t key_size = ft_strlen(key_cstr) + 1; /* include null terminator */

  return map_set(m, key_cstr, key_size, value, value_size,
                 owned_flags | MAP_OWN_KEY, free, del_value);
}
