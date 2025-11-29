/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:58:57 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/20 11:08:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"

ssize_t io_push_uint(int fd, uint64_t n) {
  char buffer[32];
  size_t i = 0;

  if (n == 0) {
    return io_push_cstr(fd, "0");
  }

  while (n > 0) {
    buffer[i++] = (char)('0' + (n % 10));
    n /= 10;
  }
  // Reverse the buffer
  for (size_t j = 0; j < i / 2; j++) {
    char temp = buffer[j];
    buffer[j] = buffer[i - j - 1];
    buffer[i - j - 1] = temp;
  }
  return io_push_cstr(fd, buffer);
}
