/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:44:23 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:47:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "42/memory/ops.h"

/*
 * Tests for ft_memset. We compare results with the standard libc memset where
 * appropriate and also assert return value and boundary behaviours.
 */

static void fill_pattern(unsigned char* buf, size_t size, unsigned char start) {
  for (size_t i = 0; i < size; ++i)
    buf[i] = (unsigned char)(start + (unsigned)i);
}

Test(ft_memset, fill_with_zero) {
  unsigned char buf[32];

  fill_pattern(buf, sizeof(buf), 1);
  void* ret = ft_memset(buf, 0, sizeof(buf));
  cr_assert_eq(ret, buf, "ft_memset should return the destination pointer");
  for (size_t i = 0; i < sizeof(buf); ++i)
    cr_assert_eq(buf[i], 0, "byte %zu should be zero", i);
}

Test(ft_memset, fill_with_ff) {
  unsigned char buf[16];

  memset(buf, 0, sizeof(buf));
  ft_memset(buf, 0xFF, sizeof(buf));
  for (size_t i = 0; i < sizeof(buf); ++i)
    cr_assert_eq(buf[i], 0xFF, "byte %zu should be 0xFF", i);
}

Test(ft_memset, fill_middle_section) {
  unsigned char buf[12];

  fill_pattern(buf, sizeof(buf), 0x10);
  unsigned char expected[sizeof(buf)];
  memcpy(expected, buf, sizeof(buf));

  /* change bytes 3..6 (4 bytes) */
  ft_memset(buf + 3, 0x22, 4);
  memset(expected + 3, 0x22, 4);

  cr_assert_arr_eq(buf, expected, sizeof(buf));
}

Test(ft_memset, zero_length_set) {
  unsigned char buf[8];

  fill_pattern(buf, sizeof(buf), 0x5);
  unsigned char before[sizeof(buf)];
  memcpy(before, buf, sizeof(buf));

  void* ret = ft_memset(buf, 0x33, 0);
  cr_assert_eq(ret, buf, "return pointer must be dest even for n=0");
  cr_assert_arr_eq(buf, before, sizeof(buf));
}

Test(ft_memset, return_value_is_s) {
  char stack[4];
  char* ret = ft_memset(stack, 'A', 4);
  cr_assert_eq(ret, stack);
}

Test(ft_memset, large_fill_pattern) {
  size_t n = 4096;
  unsigned char* a = malloc(n);
  unsigned char* b = malloc(n);
  cr_assert_not_null(a);
  cr_assert_not_null(b);

  /* initialize with different values to ensure overwrite */
  memset(a, 0xAA, n);
  memset(b, 0xAA, n);

  ft_memset(a, 0x7D, n);
  memset(b, 0x7D, n);

  cr_assert_arr_eq(a, b, n);
  free(a);
  free(b);
}

Test(ft_memset, binary_region_with_prior_noise) {
  unsigned char buf[20];

  /* put "noise" (non-zero) everywhere */
  for (size_t i = 0; i < sizeof(buf); ++i) buf[i] = (unsigned char)(i * 13 + 7);

  /* only the first 5 bytes should be overwritten */
  ft_memset(buf, 0x00, 5);
  for (size_t i = 0; i < 5; ++i)
    cr_assert_eq(buf[i], 0, "byte %zu should be zero", i);
  for (size_t i = 5; i < sizeof(buf); ++i)
    cr_assert_neq(buf[i], 0, "byte %zu should be untouched and non-zero", i);
}

Test(ft_memset, repeated_calls_chain) {
  unsigned char buf[10];

  memset(buf, 0, sizeof(buf));
  ft_memset(buf, 0x11, 3);
  ft_memset(buf + 3, 0x22, 3);
  ft_memset(buf + 6, 0x33, 4);

  for (size_t i = 0; i < 3; ++i) cr_assert_eq(buf[i], 0x11);
  for (size_t i = 3; i < 6; ++i) cr_assert_eq(buf[i], 0x22);
  for (size_t i = 6; i < 10; ++i) cr_assert_eq(buf[i], 0x33);
}

Test(ft_memset, random_fill_values) {
  unsigned char buf1[6];
  unsigned char buf2[6];

  fill_pattern(buf1, sizeof(buf1), 1);
  memcpy(buf2, buf1, sizeof(buf1));

  /* test negative value (-1) -> 0xFF */
  ft_memset(buf1, -1, sizeof(buf1));
  memset(buf2, 0xFF, sizeof(buf2));
  cr_assert_arr_eq(buf1, buf2, sizeof(buf1));

  fill_pattern(buf1, sizeof(buf1), 10);
  memcpy(buf2, buf1, sizeof(buf1));

  /* test value 256 -> treated as 0 */
  ft_memset(buf1, 256, 2);
  memset(buf2, 0, 2);
  cr_assert_arr_eq(buf1, buf2, sizeof(buf1));
}
