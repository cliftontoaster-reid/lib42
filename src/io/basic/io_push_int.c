/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:52:08 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 20:20:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"

ssize_t io_push_int(int fd, int64_t n) {
  char buffer[32];
  uint64_t un;
  size_t i = 0;
  ssize_t bytes_written = 0;

  if (n == 0) {
    return io_push_cstr(fd, "0");
  }
  if (n < 0) {
    ssize_t w = io_push_cstr(fd, "-");
    if (w < 0) return -1;
    bytes_written += w;
    un = (uint64_t)(-n);
  } else {
    un = (uint64_t)n;
  }

  while (un > 0) {
    buffer[i++] = (char)('0' + (un % 10));
    un /= 10;
  }
  // Reverse the buffer
  for (size_t j = 0; j < i / 2; j++) {
    char temp = buffer[j];
    buffer[j] = buffer[i - j - 1];
    buffer[i - j - 1] = temp;
  }
  buffer[i] = '\0';
  ssize_t w = io_push_cstr(fd, buffer);
  if (w < 0) return -1;
  return bytes_written + w;
}
