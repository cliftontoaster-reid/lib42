/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:06:09 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:40:34 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"
#include "42/memory/cstr.h"

/**
 * @brief Writes a C-style string to the specified file descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param str The string to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_cstr(int fd, const char* str) {
  if (fd < 0 || str == NULL) return -1;

  size_t len = ft_strlen(str);

  return write(fd, str, len);
}

/**
 * @brief Writes a \ref t_string to the specified file descriptor.
 * @ingroup io::write
 * @relates t_string
 * @param fd The file descriptor to write to.
 * @param str The \ref t_string to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_string(int fd, const t_string* str) {
  if (fd < 0 || str == NULL) return -1;

  return write(fd, str->data, str->size);
}
