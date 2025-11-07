/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "memory/cstr.h"

Test(ft_strncpy, copy_less_than_n) {
  char dest[10];
  memset(dest, 'x', sizeof(dest));
  const char* src = "hi";
  ft_strncpy(dest, src, 5);
  cr_assert_eq(dest[0], 'h');
  cr_assert_eq(dest[1], 'i');
  /* should pad with nulls */
  cr_assert_eq(dest[2], '\0');
  cr_assert_eq(dest[3], '\0');
  cr_assert_eq(dest[4], '\0');
}

Test(ft_strncpy, copy_exactly_n) {
  char dest[10];
  memset(dest, 'x', sizeof(dest));
  const char* src = "hello";
  ft_strncpy(dest, src, 5);
  cr_assert_eq(memcmp(dest, "hello", 5), 0);
}

Test(ft_strncpy, n_larger_than_src_pads_nulls) {
  char dest[10];
  memset(dest, 'x', sizeof(dest));
  const char* src = "abc";
  ft_strncpy(dest, src, 7);
  cr_assert_eq(dest[0], 'a');
  cr_assert_eq(dest[1], 'b');
  cr_assert_eq(dest[2], 'c');
  for (int i = 3; i < 7; i++) {
    cr_assert_eq(dest[i], '\0');
  }
}

Test(ft_strncpy, n_zero_no_copy) {
  char dest[10] = "original";
  const char* src = "new";
  ft_strncpy(dest, src, 0);
  cr_assert_str_eq(dest, "original");
}

Test(ft_strncpy, returns_dest) {
  char dest[10];
  const char* src = "test";
  char* ret = ft_strncpy(dest, src, 5);
  cr_assert_eq(ret, dest);
}

Test(ft_strncpy, no_null_terminator_when_n_equals_len) {
  char dest[10];
  memset(dest, 'x', sizeof(dest));
  const char* src = "hello";
  ft_strncpy(dest, src, 5);
  /* no null terminator added when n == strlen(src) */
  cr_assert_eq(dest[5], 'x');
}

Test(ft_strncpy, src_longer_than_n) {
  char dest[10];
  memset(dest, 'x', sizeof(dest));
  const char* src = "hello world";
  ft_strncpy(dest, src, 5);
  cr_assert_eq(memcmp(dest, "hello", 5), 0);
  cr_assert_eq(dest[5], 'x'); /* no null terminator */
}

Test(ft_strncpy, empty_string_pads_with_nulls) {
  char dest[5];
  memset(dest, 'x', sizeof(dest));
  const char* src = "";
  ft_strncpy(dest, src, 5);
  for (int i = 0; i < 5; i++) {
    cr_assert_eq(dest[i], '\0');
  }
}

Test(ft_strncpy, comparison_with_libc) {
  char dest1[20];
  char dest2[20];
  memset(dest1, 'y', sizeof(dest1));
  memset(dest2, 'y', sizeof(dest2));
  const char* src = "test";
  ft_strncpy(dest1, src, 10);
  strncpy(dest2, src, 10);
  cr_assert_eq(memcmp(dest1, dest2, 20), 0);
}

Test(ft_strncpy, partial_copy) {
  char dest[10];
  memset(dest, 'z', sizeof(dest));
  const char* src = "abcdefgh";
  ft_strncpy(dest, src, 3);
  cr_assert_eq(memcmp(dest, "abc", 3), 0);
  cr_assert_eq(dest[3], 'z');
}
