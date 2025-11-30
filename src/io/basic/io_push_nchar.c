/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_nchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:04:27 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:40:12 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"

/**
 * @param fd The file descriptor to write to.
 * @param c The character to write.
 * @param n The number of times to write the character.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_nchar(int fd, char c, size_t n) {
  if (fd < 0) return -1;

  ssize_t total_written = 0;

  for (size_t i = 0; i < n; i++) {
    ssize_t written = write(fd, &c, 1);
    if (written < 0) {
      return total_written > 0 ? total_written : -1;
    }
    total_written += written;
  }
  return total_written;
}
