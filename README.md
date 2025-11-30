# lib42

[![Build Status](https://img.shields.io/github/actions/workflow/status/cliftontoaster-reid/lib42/ci.yml)](https://github.com/cliftontoaster-reid/lib42/actions)
[![Release](https://img.shields.io/github/v/release/cliftontoaster-reid/lib42)](https://github.com/cliftontoaster-reid/lib42/releases)
[![License](https://img.shields.io/github/license/cliftontoaster-reid/lib42)](https://github.com/cliftontoaster-reid/lib42/blob/main/LICENSE)
[![Repo size](https://img.shields.io/github/repo-size/cliftontoaster-reid/lib42)](https://github.com/cliftontoaster-reid/lib42)
[![Stars](https://img.shields.io/github/stars/cliftontoaster-reid/lib42?style=flat)](https://github.com/cliftontoaster-reid/lib42/stargazers)
[![Issues](https://img.shields.io/github/issues/cliftontoaster-reid/lib42)](https://github.com/cliftontoaster-reid/lib42/issues)
[![Last commit](https://img.shields.io/github/last-commit/cliftontoaster-reid/lib42)](https://github.com/cliftontoaster-reid/lib42/commits)
![Test Coverage](https://img.shields.io/codecov/c/github/cliftontoaster-reid/lib42)

A comprehensive C library inspired by 42 school's libft, offering a wide range of utilities for memory management, string manipulation, data structures, and more.

## Features

- **Character classification toolkit** – Drop-in replacements for the usual `is*`
  family (`ft_isalpha`, `ft_isdigit`, `ft_isascii`, `ft_tolower`, `ft_toupper`,
  and friends) implemented in plain C, making it easy to reason about input
  validation without pulling in the C locale machinery.
- **Robust C-string helpers** – A rich set of `ft_str*` utilities covering
  copying, concatenation, searching, and duplication, including extended
  helpers like `ft_strlcat`, `ft_strndup`, and `ft_strrstr` for safer text
  manipulation.
- **Low-level memory primitives** – Carefully crafted `ft_mem*` routines for
  copying, moving, scanning, and filling raw buffers (`ft_memcpy`,
  `ft_memmove`, `ft_memmem`, `ft_memrchr`, `ft_mempcpy`, ...), letting you work
  with binary data while keeping the API consistent.
- **Generic singly linked list API** – Minimal `t_list` structure with helpers
  for constructing, iterating, mapping, and cleaning up lists, so you can build
  lightweight data structures without reinventing the wheel each time.
- **Modern build & packaging** – CMake project with both static and shared
  targets, warning-clean builds (`-Wall -Wextra -Werror`), install rules, and a
  generated `42.pc` pkg-config file for painless consumption downstream.
- **Optional Criterion test suite integration** – Plug in Criterion via
  CTest to run the bundled unit tests automatically whenever the
  framework is available, promoting confident refactors.
