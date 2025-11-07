/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
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

Test(ft_strcat, append_to_empty) {
  char dest[20] = "";
  const char* src = "hello";
  ft_strcat(dest, src);
  cr_assert_str_eq(dest, "hello");
}

Test(ft_strcat, append_to_existing) {
  char dest[20] = "hello";
  const char* src = " world";
  ft_strcat(dest, src);
  cr_assert_str_eq(dest, "hello world");
}

Test(ft_strcat, returns_dest) {
  char dest[20] = "test";
  const char* src = "ing";
  char* ret = ft_strcat(dest, src);
  cr_assert_eq(ret, dest);
}

Test(ft_strcat, append_empty_string) {
  char dest[20] = "hello";
  const char* src = "";
  ft_strcat(dest, src);
  cr_assert_str_eq(dest, "hello");
}

Test(ft_strcat, null_terminator_added) {
  char dest[20] = "abc";
  const char* src = "def";
  ft_strcat(dest, src);
  cr_assert_eq(dest[6], '\0');
}

Test(ft_strcat, multiple_appends) {
  char dest[30] = "a";
  ft_strcat(dest, "b");
  ft_strcat(dest, "c");
  ft_strcat(dest, "d");
  cr_assert_str_eq(dest, "abcd");
}

Test(ft_strcat, append_with_special_chars) {
  char dest[30] = "hello";
  const char* src = "\t\n!";
  ft_strcat(dest, src);
  cr_assert_str_eq(dest, "hello\t\n!");
}

Test(ft_strcat, comparison_with_libc) {
  char dest1[50] = "prefix";
  char dest2[50] = "prefix";
  const char* src = " suffix";
  ft_strcat(dest1, src);
  strcat(dest2, src);
  cr_assert_str_eq(dest1, dest2);
}

Test(ft_strcat, long_concatenation) {
  char dest[100] = "start ";
  const char* src = "this is a longer string to append";
  ft_strcat(dest, src);
  cr_assert_str_eq(dest, "start this is a longer string to append");
}

Test(ft_strcat, single_char_append) {
  char dest[10] = "hi";
  const char* src = "!";
  ft_strcat(dest, src);
  cr_assert_str_eq(dest, "hi!");
}
