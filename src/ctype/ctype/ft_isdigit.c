/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:46:34 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:55:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ctype/ctype.h"

bool ft_isdigit(char c) {
  unsigned char uc = (unsigned char)c;
  return uc >= '0' && uc <= '9';
}
