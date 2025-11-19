/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/memory/cstr.h"

Test(ft_strlcat, normal_append) {
  char dest[20] = "hello";
  const char* src = " world";
  size_t ret = ft_strlcat(dest, src, 20);
  cr_assert_str_eq(dest, "hello world");
  cr_assert_eq(ret, 11);
}

Test(ft_strlcat, return_value_is_total_length) {
  char dest[20] = "abc";
  const char* src = "def";
  size_t ret = ft_strlcat(dest, src, 20);
  cr_assert_eq(ret, 6); /* strlen("abc") + strlen("def") */
}

Test(ft_strlcat, truncation_occurs) {
  char dest[10] = "hello";
  const char* src = " world";
  size_t ret = ft_strlcat(dest, src, 10);
  cr_assert_eq(ret, 11);         /* would have been 11 if enough space */
  cr_assert_eq(strlen(dest), 9); /* only fits 9 chars + null */
  cr_assert_eq(dest[9], '\0');
}

Test(ft_strlcat, size_too_small) {
  char dest[20] = "hello";
  const char* src = " world";
  size_t ret = ft_strlcat(dest, src, 3);
  /* size <= strlen(dest), so returns strlen(dest) + strlen(src) */
  cr_assert_eq(ret, 5 + 6);
  /* dest should not be modified when size <= initial length */
  cr_assert_str_eq(dest, "hello");
}

Test(ft_strlcat, size_equals_dest_len) {
  char dest[20] = "abc";
  const char* src = "def";
  size_t ret = ft_strlcat(dest, src, 3);
  cr_assert_eq(ret, 6); /* 3 + 3 */
  cr_assert_str_eq(dest, "abc");
}

Test(ft_strlcat, size_zero) {
  char dest[20] = "test";
  const char* src = "ing";
  size_t ret = ft_strlcat(dest, src, 0);
  cr_assert_eq(ret, 4 + 3); /* strlen(dest) + strlen(src) */
  cr_assert_str_eq(dest, "test");
}

Test(ft_strlcat, append_to_empty) {
  char dest[20] = "";
  const char* src = "hello";
  size_t ret = ft_strlcat(dest, src, 20);
  cr_assert_str_eq(dest, "hello");
  cr_assert_eq(ret, 5);
}

Test(ft_strlcat, empty_src) {
  char dest[20] = "test";
  const char* src = "";
  size_t ret = ft_strlcat(dest, src, 20);
  cr_assert_str_eq(dest, "test");
  cr_assert_eq(ret, 4);
}

Test(ft_strlcat, exact_fit) {
  char dest[12] = "hello";
  const char* src = " world";
  size_t ret = ft_strlcat(dest, src, 12);
  cr_assert_str_eq(dest, "hello world");
  cr_assert_eq(ret, 11);
}

Test(ft_strlcat, one_char_space) {
  char dest[7] = "hello";
  const char* src = " world";
  size_t ret = ft_strlcat(dest, src, 7);
  cr_assert_eq(ret, 11);            /* intended length */
  cr_assert_str_eq(dest, "hello "); /* only one char could fit */
  cr_assert_eq(dest[6], '\0');
}

Test(ft_strlcat, null_terminated_always) {
  char dest[8] = "abc";
  const char* src = "defghijk";
  ft_strlcat(dest, src, 8);
  cr_assert_eq(dest[7], '\0');
}
