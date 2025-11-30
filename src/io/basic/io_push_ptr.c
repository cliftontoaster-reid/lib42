/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:01:09 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:40:24 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"

/**
 * @brief Writes the pointer address in hexadecimal format to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param ptr The pointer whose address to write.
 * @param uppercase If true, uses uppercase letters (A-F); otherwise, lowercase
 * (a-f).
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_ptr(int fd, const void* ptr, bool uppercase) {
  if (fd < 0) return -1;

  uintptr_t address = (uintptr_t)ptr;
  ssize_t bytes_written = 0;

  // Write the "0x" prefix
  bytes_written += io_push_cstr(fd, "0x");

  // Write the address in hexadecimal format
  bytes_written += io_push_hex(fd, address, uppercase);

  return bytes_written;
}
