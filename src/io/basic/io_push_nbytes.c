/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_nbytes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:56:13 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:40:08 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"

/**
 * @brief Writes n bytes from the buffer to the file descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param buf The buffer to write from.
 * @param n The number of bytes to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_nbytes(int fd, const void* buf, size_t n) {
  if (fd < 0 || buf == NULL) return -1;

  ssize_t total_written = 0;
  const char* buffer = (const char*)buf;

  while (n > 0) {
    ssize_t written = write(fd, buffer + total_written, n);
    if (written < 0) {
      return total_written > 0 ? total_written : -1;
    }
    total_written += written;
    n -= written;
  }
  return total_written;
}