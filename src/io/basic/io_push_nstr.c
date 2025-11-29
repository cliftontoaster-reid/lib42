/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_nstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:24:03 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 19:41:22 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"
#include "42/memory/cstr.h"

/**
 * @brief Writes up to n characters from the C-style string to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param str The string to write from.
 * @param n The maximum number of characters to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_ncstr(int fd, const char* str, size_t n) {
  size_t len = ft_strlen(str);

  return write(fd, str, n >= len ? len : n);
}
