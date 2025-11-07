/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mempcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@invalid>                   +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:50:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 10:50:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "memory/ops.h"

Test(ft_mempcpy, basic_copy_return_advanced_pointer) {
  unsigned char src[] = {1, 2, 3, 4};
  unsigned char dest[4] = {0};
  void* p = ft_mempcpy(dest, src, 4);
  cr_assert_eq(p, dest + 4);
  cr_assert_arr_eq(dest, src, 4);
}

Test(ft_mempcpy, zero_length_returns_dest) {
  unsigned char src[] = {9, 9};
  unsigned char dest[] = {7, 7};
  void* p = ft_mempcpy(dest, src, 0);
  cr_assert_eq(p, dest);
  unsigned char expected[] = {7, 7};
  cr_assert_arr_eq(dest, expected, 2);
}

Test(ft_mempcpy, large_copy_return_pointer_correct) {
  size_t n = 2048;
  unsigned char* src = malloc(n);
  unsigned char* dest = malloc(n);
  cr_assert_not_null(src);
  cr_assert_not_null(dest);
  for (size_t i = 0; i < n; ++i) src[i] = (unsigned char)(i & 0xFF);
  void* p = ft_mempcpy(dest, src, n);
  cr_assert_eq(p, dest + n);
  cr_assert_arr_eq(dest, src, n);
  free(src);
  free(dest);
}

Test(ft_mempcpy, binary_copy_with_nulls) {
  unsigned char src[] = {0, 1, 0, 2, 0};
  unsigned char dest[5] = {0xFF};
  void* p = ft_mempcpy(dest, src, 5);
  cr_assert_eq(p, dest + 5);
  cr_assert_arr_eq(dest, src, 5);
}

Test(ft_mempcpy, chain_copy_usage) {
  unsigned char src1[] = {1, 2};
  unsigned char src2[] = {3, 4};
  unsigned char buf[4];
  unsigned char* p = ft_mempcpy(buf, src1, 2);
  p = ft_mempcpy(p, src2, 2);
  cr_assert_eq(p, buf + 4);
  unsigned char expected[] = {1, 2, 3, 4};
  cr_assert_arr_eq(buf, expected, 4);
}

Test(ft_mempcpy, return_pointer_write_follow_up) {
  unsigned char src[] = {9, 8, 7};
  unsigned char dest[6] = {0};
  unsigned char* p = ft_mempcpy(dest, src, 3);
  /* write a trailing byte */
  *p = 0xFF;
  cr_assert_eq(dest[3], 0xFF);
}

Test(ft_mempcpy, copy_high_bytes) {
  unsigned char src[] = {0x80, 0xFF, 0x7F};
  unsigned char dest[3] = {0};
  ft_mempcpy(dest, src, 3);
  cr_assert_arr_eq(dest, src, 3);
}

Test(ft_mempcpy, random_copy_sequences) {
  srand(3);
  for (int t = 0; t < 200; ++t) {
    size_t n = rand() % 256;
    unsigned char* src = malloc(n ? n : 1);
    unsigned char* d1 = malloc(n ? n : 1);
    unsigned char* d2 = malloc(n ? n : 1);
    cr_assert_not_null(src);
    cr_assert_not_null(d1);
    cr_assert_not_null(d2);
    for (size_t i = 0; i < n; ++i) src[i] = rand() & 0xFF;
    void* p1 = ft_mempcpy(d1, src, n);
    void* p2 = memcpy(d2, src, n) + n;
    cr_assert_eq((unsigned char*)p1 - d1, (unsigned char*)p2 - d2);
    cr_assert_arr_eq(d1, d2, n);
    free(src);
    free(d1);
    free(d2);
  }
}

Test(ft_mempcpy, stress_many_sequential_calls) {
  unsigned char big[1024];
  for (int i = 0; i < 1024; ++i) big[i] = (unsigned char)(i & 0xFF);
  unsigned char dest[1024];
  unsigned char* p = dest;
  for (int i = 0; i < 16; ++i) {
    p = ft_mempcpy(p, big + (i * 64), 64);
  }
  cr_assert_arr_eq(dest, big, 1024);
}
