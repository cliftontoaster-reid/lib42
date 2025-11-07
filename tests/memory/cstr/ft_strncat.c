/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
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

Test(ft_strncat, append_n_chars) {
  char dest[20] = "hello";
  const char* src = " world";
  ft_strncat(dest, src, 3);
  cr_assert_str_eq(dest, "hello wo");
}

Test(ft_strncat, n_larger_than_src) {
  char dest[20] = "hi";
  const char* src = "!";
  ft_strncat(dest, src, 10);
  cr_assert_str_eq(dest, "hi!");
}

Test(ft_strncat, n_zero) {
  char dest[20] = "test";
  const char* src = "ing";
  ft_strncat(dest, src, 0);
  cr_assert_str_eq(dest, "test");
}

Test(ft_strncat, returns_dest) {
  char dest[20] = "abc";
  const char* src = "def";
  char* ret = ft_strncat(dest, src, 3);
  cr_assert_eq(ret, dest);
}

Test(ft_strncat, append_to_empty) {
  char dest[20] = "";
  const char* src = "hello";
  ft_strncat(dest, src, 5);
  cr_assert_str_eq(dest, "hello");
}

Test(ft_strncat, null_terminated) {
  char dest[20] = "abc";
  const char* src = "defgh";
  ft_strncat(dest, src, 3);
  cr_assert_eq(dest[6], '\0');
  cr_assert_str_eq(dest, "abcdef");
}

Test(ft_strncat, partial_append) {
  char dest[30] = "start";
  const char* src = "1234567890";
  ft_strncat(dest, src, 5);
  cr_assert_str_eq(dest, "start12345");
}

Test(ft_strncat, comparison_with_libc) {
  char dest1[50] = "prefix";
  char dest2[50] = "prefix";
  const char* src = " suffix test";
  ft_strncat(dest1, src, 7);
  strncat(dest2, src, 7);
  cr_assert_str_eq(dest1, dest2);
}

Test(ft_strncat, empty_src) {
  char dest[20] = "test";
  const char* src = "";
  ft_strncat(dest, src, 5);
  cr_assert_str_eq(dest, "test");
}

Test(ft_strncat, multiple_calls) {
  char dest[30] = "a";
  ft_strncat(dest, "bc", 2);
  ft_strncat(dest, "def", 2);
  ft_strncat(dest, "ghijk", 3);
  cr_assert_str_eq(dest, "abcdeghi");
}
