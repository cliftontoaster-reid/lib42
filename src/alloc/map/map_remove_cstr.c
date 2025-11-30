/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_remove_cstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:54:40 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 14:54:50 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "42/alloc/map.int.h"

int map_remove_cstr(t_map* m, const char* key_cstr) {
  if (m == NULL || key_cstr == NULL) {
    errno = EINVAL;
    return false;
  }

  size_t key_size = ft_strlen(key_cstr) + 1; /* include null terminator */

  return map_remove(m, key_cstr, key_size);
}
