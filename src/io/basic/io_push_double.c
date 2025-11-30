/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:13:18 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:39:41 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/io/basic.h"

#define DOUBLE_MAX_PRECISION 18

static uint64_t power_of_10(int exp) {
  uint64_t result = 1;
  for (int i = 0; i < exp; i++) {
    result *= 10;
  }
  return result;
}

/**
 * @brief Writes a double as a string with specified precision to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The double to write.
 * @param precision The number of decimal places to include (max 18).
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_double(int fd, double n, int precision) {
  if (fd < 0) return -1;

  ssize_t bytes_written = 0;
  uint64_t int_part;
  uint64_t frac_part;
  uint64_t scale;

  // Handle special cases
  if (n != n) return io_push_cstr(fd, "nan");
  if (n == 1.0 / 0.0) return io_push_cstr(fd, "inf");
  if (n == -1.0 / 0.0) return io_push_cstr(fd, "-inf");

  // Clamp precision
  if (precision > DOUBLE_MAX_PRECISION) precision = DOUBLE_MAX_PRECISION;
  if (precision < 0) precision = 0;

  // Handle negative
  if (n < 0) {
    bytes_written += io_push_cstr(fd, "-");
    n = -n;
  }

  scale = power_of_10(precision);
  int_part = (uint64_t)n;
  frac_part = (uint64_t)((n - (double)int_part) * (double)scale + 0.5);

  // Handle rounding overflow (e.g., 0.9999 with precision 2 -> 1.00)
  if (frac_part >= scale) {
    int_part++;
    frac_part = 0;
  }

  // Write integer part
  bytes_written += io_push_uint(fd, int_part);

  // Write fractional part
  if (precision > 0) {
    bytes_written += io_push_cstr(fd, ".");
    // Write leading zeros
    uint64_t threshold = scale / 10;
    while (threshold > 0 && frac_part < threshold) {
      bytes_written += io_push_cstr(fd, "0");
      threshold /= 10;
    }
    // Write remaining digits
    if (frac_part > 0) bytes_written += io_push_uint(fd, frac_part);
  }

  return bytes_written;
}
