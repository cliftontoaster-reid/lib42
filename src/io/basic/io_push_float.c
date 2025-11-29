/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:10:02 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/29 19:12:08 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "42/io/basic.h"

/**
 * @brief Writes a float as a string with specified precision to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The float to write.
 * @param precision The number of decimal places to include.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_float(int fd, float n, int precision) {
  return io_push_double(fd, (double)n, precision);
}
