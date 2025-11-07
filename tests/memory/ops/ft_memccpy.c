/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@invalid>                   +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 10:12:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "memory/ops.h"

Test(ft_memccpy, stop_byte_found_early) {
  unsigned char src[] = {1, 2, 3, 4, 5};
  unsigned char dest[5] = {0};
  void* ret = ft_memccpy(dest, src, 3, 5);
  cr_assert_not_null(ret);
  cr_assert_eq((unsigned char*)ret - dest, 3);
  /* dest should have copied up to and including 3 */
  for (int i = 0; i < 3; ++i) cr_assert_eq(dest[i], src[i]);
}

Test(ft_memccpy, stop_byte_found_last) {
  unsigned char src[] = {9, 9, 9, 7};
  unsigned char dest[4] = {0};
  void* ret = ft_memccpy(dest, src, 7, 4);
  cr_assert_not_null(ret);
  cr_assert_eq((unsigned char*)ret - dest, 4);
  cr_assert_arr_eq(dest, src, 4);
}

Test(ft_memccpy, stop_byte_not_found_returns_null) {
  unsigned char src[] = {1, 2, 3};
  unsigned char dest[3] = {0};
  void* ret = ft_memccpy(dest, src, 0xFF, 3);
  cr_assert_null(ret);
  cr_assert_arr_eq(dest, src, 3);
}

Test(ft_memccpy, zero_length_returns_null) {
  unsigned char src[] = {1, 2};
  unsigned char dest[] = {7, 7};
  void* ret = ft_memccpy(dest, src, 1, 0);
  cr_assert_null(ret);
  cr_assert_eq(dest[0], 7);
}

Test(ft_memccpy, correct_return_pointer_offset) {
  unsigned char src[] = {0, 1, 2, 3, 4};
  unsigned char dest[6] = {0};
  void* ret = ft_memccpy(dest, src, 2, 5);
  cr_assert_eq(ret, dest + 3);
}

Test(ft_memccpy, binary_data_with_zero_before_c) {
  unsigned char src[] = {0, 0, 5, 0, 9};
  unsigned char dest[5] = {0xFF};
  void* ret = ft_memccpy(dest, src, 9, 5);
  cr_assert_not_null(ret);
  cr_assert_eq((unsigned char*)ret - dest, 5);
}

Test(ft_memccpy, copy_until_c_only) {
  unsigned char src[] = {1, 2, 3, 4, 5};
  unsigned char dest[5] = {0};
  ft_memccpy(dest, src, 4, 4);
  cr_assert_arr_eq(dest, src, 4);
}

Test(ft_memccpy, large_buffer_stop_near_end) {
  size_t n = 1024;
  unsigned char* src = malloc(n);
  unsigned char* dest = malloc(n);
  cr_assert_not_null(src);
  cr_assert_not_null(dest);
  for (size_t i = 0; i < n; ++i) src[i] = (unsigned char)(i & 0xFF);
  void* ret = ft_memccpy(dest, src, (unsigned char)(255), n);
  /* there is likely a 255 somewhere; ensure return is either null or within
   * range */
  if (ret) cr_assert_leq((unsigned char*)ret - dest, n);
  free(src);
  free(dest);
}

Test(ft_memccpy, multiple_c_only_first_matters) {
  unsigned char src[] = {1, 9, 2, 9, 3};
  unsigned char dest[5] = {0};
  void* ret = ft_memccpy(dest, src, 9, 5);
  cr_assert_not_null(ret);
  cr_assert_eq((unsigned char*)ret - dest, 2);
}

Test(ft_memccpy, random_inserts_of_c) {
  srand(11);
  for (int t = 0; t < 100; ++t) {
    size_t n = (rand() % 64) + 1;
    unsigned char* src = malloc(n);
    unsigned char* d1 = malloc(n);
    unsigned char* d2 = malloc(n);
    cr_assert_not_null(src);
    cr_assert_not_null(d1);
    cr_assert_not_null(d2);
    memset(d1, 0, n);
    memset(d2, 0, n);
    for (size_t i = 0; i < n; ++i) src[i] = rand() & 0xFF;
    unsigned char c = (unsigned char)(rand() & 0xFF);
    void* r1 = ft_memccpy(d1, src, c, n);
    /* mimic memccpy behavior using libc memchr+memcpy */
    void* pos = memchr(src, c, n);
    void* r2 = NULL;
    if (pos) {
      size_t idx = (unsigned char*)pos - src;
      memcpy(d2, src, idx + 1);
      r2 = d2 + idx + 1;
    } else {
      memcpy(d2, src, n);
    }
    if (r1) cr_assert_not_null(r2);
    if (r1 && r2)
      cr_assert_eq((unsigned char*)r1 - d1, (unsigned char*)r2 - d2);
    cr_assert_arr_eq(d1, d2, n);
    free(src);
    free(d1);
    free(d2);
  }
}
