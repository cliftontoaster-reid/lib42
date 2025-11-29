/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:07:39 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/29 23:50:16 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

/**
 * @brief Singly linked list node structure.
 *
 * \ref t_list represents a single node in a singly linked list. Each node
 * contains a pointer to arbitrary content and a pointer to the next node
 * in the list.
 *
 * @warning It is highly discouraged to manipulate the internal pointers
 *          directly. Use the provided list functions to ensure correct
 *          behavior and to avoid memory corruption.
 */
typedef struct s_list {
  /// @publicsection

  /// @brief Pointer to the content stored in the node.
  ///
  /// This pointer is NOT owned by the t_list instance and should be
  /// provided a del function when freeing the list if the content needs to be
  /// freed.
  ///
  /// @warning If a del function is not provided, the content will not be freed
  ///          when the node is deleted, potentially causing memory leaks.
  ///          see \ref ft_lstdelone and \ref ft_lstclear for details.
  ///
  /// @see ft_lstdelone
  /// @see ft_lstclear
  void* content;
  /// @brief Pointer to the next node in the list.
  ///
  /// This pointer is NULL if this node is the last in the list.
  ///
  /// @warning Do not modify this field directly. If a node has this pointer
  ///          changed to a NULL for example, the children nodes will be left
  ///          dangling and inaccessible, causing memory leaks.
  struct s_list* next;
} t_list;

/**
 * @brief Create a new list node
 *
 * Allocates a new t_list node and sets its content pointer to @p content.
 * The new node's next pointer is initialized to NULL.
 *
 * @param content Pointer to the data to store in the node. May be NULL.
 * @return A pointer to the newly allocated node on success, or NULL if
 *         allocation fails.
 * @warning This function allocates memory for the returned node using
 *          malloc. The caller takes ownership of the returned node and is
 *          responsible for freeing it (for example with ft_lstdelone or
 *          ft_lstclear using an appropriate @c del function for the
 *          node's content). Failure to free the node will cause a memory
 *          leak.
 */
t_list* ft_lstnew(void* content);

/**
 * @brief Insert a node at the beginning of a list
 *
 * Adds the node @p new at the start of the list pointed to by @p lst.
 * If @p lst is NULL or *lst is NULL, @p new becomes the first node.
 * The function does not allocate or free memory for node contents; it only
 * adjusts pointers.
 *
 * @param lst Address of a pointer to the first node of the list. If NULL,
 *            the function does nothing.
 * @param new The node to insert. It may be NULL (in which case the list is
 *            unchanged), but its next pointer will be set to the previous
 *            head when inserted.
 */
void ft_lstadd_front(t_list** lst, t_list* new);

/**
 * @brief Append a node to the end of a list
 *
 * Traverses the list pointed to by @p lst and appends the node @p new as the
 * last element. If the list is empty (NULL or *lst == NULL), @p new becomes
 * the first node.
 *
 * @param lst Address of a pointer to the first node of the list. If NULL,
 *            the function does nothing.
 * @param new The node to append. If NULL, the list is left unchanged.
 */
void ft_lstadd_back(t_list** lst, t_list* new);

/**
 * @brief Compute the number of nodes in a list
 *
 * Iterates through the list starting at @p lst and returns the number of
 * nodes found.
 *
 * @param lst Pointer to the first node of the list (may be NULL).
 * @return The number of nodes in the list. Returns 0 if @p lst is NULL.
 */
size_t ft_lstsize(t_list* lst);

/**
 * @brief Get the last node of a list
 *
 * Traverses the list starting at @p lst and returns a pointer to the last
 * node (the node whose next is NULL). If @p lst is NULL the function
 * returns NULL.
 *
 * @param lst Pointer to the first node of the list (may be NULL).
 * @return Pointer to the last node, or NULL if the list is empty.
 */
t_list* ft_lstlast(t_list* lst);

/**
 * @brief Delete a single node
 *
 * Applies the function @p del to the node's content (if @p del is not
 * NULL) and then frees the node itself. This function only deletes the
 * single node provided; it does however relink the surrounding nodes if needed.
 *
 * @param lst The node to delete. If NULL, the function does nothing.
 * @param del Function to free the node's content. If NULL, the content is
 *            not freed (use with care to avoid leaks).
 */
void ft_lstdelone(t_list* lst, void (*del)(void*));

/**
 * @brief Clear an entire list
 *
 * Iterates over the list referenced by *lst, applies @p del to each node's
 * content (if @p del is not NULL), frees each node, and finally sets *lst
 * to NULL.
 *
 * @param lst Address of a pointer to the first node of the list. If NULL
 *            or *lst is NULL the function does nothing.
 * @param del Function to free the node content. If NULL, the content is not
 *            freed; only the node structures themselves are freed.
 */
void ft_lstclear(t_list** lst, void (*del)(void*));

/**
 * @brief Apply a function to each element of a list
 *
 * Iterates through @p lst and calls @p f on the content pointer of each
 * node. This function does not allocate or free nodes; it is intended for
 * side-effects (e.g., printing, modifying content in-place).
 *
 * @param lst Pointer to the first node of the list. If NULL the function
 *            does nothing.
 * @param f Function to apply to each node's content. If NULL the function
 *          does nothing.
 */
void ft_lstiter(t_list* lst, void (*f)(void*));

/**
 * @brief Create a new list by transforming elements of an existing list
 *
 * Iterates the list @p lst and applies the function @p f to the content of
 * each node to build a new list whose nodes contain the transformed
 * content. If any allocation fails during the process, the function uses
 * @p del to free any content already created for the new list and frees
 * the allocated nodes before returning NULL.
 *
 * @param lst Pointer to the first node of the source list. May be NULL,
 *            in which case the function returns NULL.
 * @param f Function applied to each node's content; its return value is
 *          stored as the content of the corresponding new node. If f is
 *          NULL, behavior is undefined.
 * @param del Function used to free the content created by @p f when an
 *            allocation error occurs, or when the caller later frees the
 *            new list (recommended to provide a proper destructor).
 * @return Pointer to the first node of the newly created list on success,
 *         or NULL if allocation fails or if @p lst is NULL.
 * @warning This function allocates memory for each new node (and possibly
 *          for the transformed content returned by @p f). The caller takes
 *          ownership of the returned list and must free it (for example
 *          with ft_lstclear and the same @p del) to avoid memory leaks.
 */
t_list* ft_lstmap(t_list* lst, void* (*f)(void*), void (*del)(void*));
