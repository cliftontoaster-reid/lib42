/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:20 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:39:51 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"

#define HEX_BASE_LOWER "0123456789abcdef"
#define HEX_BASE_UPPER "0123456789ABCDEF"

ssize_t io_push_hex(int fd, uint64_t n, bool uppercase) {
  if (fd < 0) return -1;

  char buffer[32];
  size_t i = 0;
  const char* base = uppercase ? HEX_BASE_UPPER : HEX_BASE_LOWER;

  if (n == 0) {
    return io_push_cstr(fd, "0");
  }

  while (n > 0) {
    buffer[i++] = base[n % 16];
    n /= 16;
  }
  // Reverse the buffer
  for (size_t j = 0; j < i / 2; j++) {
    char temp = buffer[j];
    buffer[j] = buffer[i - j - 1];
    buffer[i - j - 1] = temp;
  }
  buffer[i] = '\0';
  return io_push_cstr(fd, buffer);
}
