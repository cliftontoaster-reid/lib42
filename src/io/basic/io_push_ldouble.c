/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_ldouble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:20:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:40:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/io/basic.h"

/*
 * Platform detection for 128-bit integer support.
 * __uint128_t is available on GCC/Clang for 64-bit targets.
 * This allows us to handle up to 38 decimal digits for the fractional part,
 * which covers 128-bit long double (quad precision, ~33-36 significant digits).
 */
#ifdef __SIZEOF_INT128__
#define HAS_UINT128 1
#define LDOUBLE_MAX_PRECISION 36
typedef __uint128_t frac_int_t;
#else
#define HAS_UINT128 0
#define LDOUBLE_MAX_PRECISION 18
typedef uint64_t frac_int_t;
#endif

static frac_int_t power_of_10_ld(int exp) {
  frac_int_t result = 1;
  for (int i = 0; i < exp; i++) {
    result *= 10;
  }
  return result;
}

/*
 * Helper to print a frac_int_t (which may be __uint128_t).
 * Since io_push_uint only handles uint64_t, we need to handle
 * large values by splitting them.
 */
static ssize_t push_frac_int(int fd, frac_int_t n) {
#if HAS_UINT128
  if (n <= UINT64_MAX) {
    return io_push_uint(fd, (uint64_t)n);
  }
  // Split into high and low parts
  // We use 10^18 as the split point (fits in uint64_t)
  const frac_int_t divisor = 1000000000000000000ULL;  // 10^18
  frac_int_t high = n / divisor;
  uint64_t low = (uint64_t)(n % divisor);

  ssize_t bytes = 0;
  // Recursively print high part
  bytes += push_frac_int(fd, high);
  // Print low part with leading zeros (must be exactly 18 digits)
  uint64_t threshold = divisor / 10;
  while (threshold > 0 && low < threshold) {
    bytes += io_push_cstr(fd, "0");
    threshold /= 10;
  }
  if (low > 0) bytes += io_push_uint(fd, low);
  return bytes;
#else
  return io_push_uint(fd, n);
#endif
}

/**
 * @brief Writes a long double as a string with specified precision to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The long double to write.
 * @param precision The number of decimal places to include.
 *                  Max 36 with __uint128_t support, otherwise max 18.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_ldouble(int fd, long double n, int precision) {
  if (fd < 0) return -1;

  ssize_t bytes_written = 0;
  uint64_t int_part;
  frac_int_t frac_part;
  frac_int_t scale;

  // Handle special cases
  if (n != n) return io_push_cstr(fd, "nan");
  if (n == 1.0L / 0.0L) return io_push_cstr(fd, "inf");
  if (n == -1.0L / 0.0L) return io_push_cstr(fd, "-inf");

  // Clamp precision
  if (precision > LDOUBLE_MAX_PRECISION) precision = LDOUBLE_MAX_PRECISION;
  if (precision < 0) precision = 0;

  // Handle negative
  if (n < 0) {
    bytes_written += io_push_cstr(fd, "-");
    n = -n;
  }

  scale = power_of_10_ld(precision);
  int_part = (uint64_t)n;
  frac_part =
      (frac_int_t)((n - (long double)int_part) * (long double)scale + 0.5L);

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
    frac_int_t threshold = scale / 10;
    while (threshold > 0 && frac_part < threshold) {
      bytes_written += io_push_cstr(fd, "0");
      threshold /= 10;
    }
    // Write remaining digits
    if (frac_part > 0) bytes_written += push_frac_int(fd, frac_part);
  }

  return bytes_written;
}
