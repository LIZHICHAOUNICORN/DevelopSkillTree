#ifndef DESIGN_DATA_STRUCTURES_LIST_
#define DESIGN_DATA_STRUCTURES_LIST_

namespace base {

#define typeof decltype

struct list_head {
  struct list_head *prev, *next;
};

#define LIST_HEAD_INIT(name) \
  { &(name), &(name) }

#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) \
  do {                      \
    (ptr)->next = (ptr);    \
    (ptr)->prev = (ptr);    \
  } while (0)

static inline void list_add_(struct list_head *n, struct list_head *prev,
                             struct list_head *next) {
  next->prev = n;
  n->next = next;
  n->prev = prev;
  prev->next = n;
}

static inline void list_del_(struct list_head *prev, struct list_head *next) {
  next->prev = prev;
  prev->next = next;
}

static inline void list_splice_(struct list_head *list,
                                struct list_head *head) {
  struct list_head *first = list->next;
  struct list_head *last = list->prev;
  struct list_head *at = head->next;

  first->prev = head;
  head->next = first;

  last->next = at;
  at->prev = last;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */

static inline void list_add(struct list_head *n, struct list_head *head) {
  list_add_(n, head, head->next);
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */

static inline void list_add_tail(struct list_head *n, struct list_head *head) {
  list_add_(n, head->prev, head);
}
/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an
 * undefined state.
 */
static inline void list_del(struct list_head *entry) {
  list_del_(entry->prev, entry->next);
  entry->next = NULL;
  entry->prev = NULL;
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static inline void list_del_init(struct list_head *entry) {
  list_del_(entry->prev, entry->next);
  INIT_LIST_HEAD(entry);
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void list_move(struct list_head *list, struct list_head *head) {
  list_del_(list->prev, list->next);
  list_add(list, head);
}
/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void list_move_tail(struct list_head *list,
                                  struct list_head *head) {
  list_del_(list->prev, list->next);
  list_add_tail(list, head);
}
/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head) {
  return head->next == head;
}

/**
 * list_splice - join two lists
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void list_splice(struct list_head *list, struct list_head *head) {
  if (!list_empty(list)) list_splice_(list, head);
}

/**
 * list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
static inline void list_splice_init(struct list_head *list,
                                    struct list_head *head) {
  if (!list_empty(list)) {
    list_splice_(list, head);
    INIT_LIST_HEAD(list);
  }
}

/**
 * list_entry - get the struct for this entry
 * @ptr:    the &struct list_head pointer.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
  (reinterpret_cast<type *>(          \
      (char *)(ptr) - (char *)(&(reinterpret_cast<type *>(1)->member)) + 1))

#define list_entry_ptr(ptr, ptrtype, member) \
  (reinterpret_cast<ptrtype>(            \
      (char *)(ptr) - (char *)(&(reinterpret_cast<ptrtype>(1)->member)) + 1))

/**
 * Move a node to the front
 */
static inline void list_mtf(struct list_head *entry, struct list_head *head) {
  if (entry->prev == head) return;
  list_del_(entry->prev, entry->next);
  list_add_(entry, head, head->next);
}

/**
 * Move a node ahead one position
 */
static inline void list_mao(struct list_head *entry, struct list_head *head) {
  // if the entry in the 1st position
  if (entry->prev == head) return;
  struct list_head *prev = entry->prev;
  list_del_(entry->prev, entry->next);
  list_add_(entry, prev->prev, prev);
}

/**
 * list_for_each    -   iterate over a list
 * @pos:    the &struct list_head to use as a loop counter.
 * @head:   the head for your list.
 */
#define list_for_each(pos, head) \
  for (pos = (head)->next; pos != (head); pos = pos->next)
/**
 * list_for_each_prev   -   iterate over a list backwards
 * @pos:    the &struct list_head to use as a loop counter.
 * @head:   the head for your list.
 */
#define list_for_each_prev(pos, head) \
  for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
 * list_for_each_safe   -   iterate over a list safe against removal of list
 * entry
 * @pos:    the &struct list_head to use as a loop counter.
 * @n:      another &struct list_head to use as temporary storage
 * @head:   the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
  for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

/**
 * list_for_each_entry  -   iterate over list of given type
 * @pos:    the type * to use as a loop counter.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#ifndef _MSC_VER
#define list_for_each_entry(pos, head, member)               \
  for (pos = list_entry_ptr((head)->next, typeof(pos), member); \
       &pos->member != (head);                               \
       pos = list_entry_ptr(pos->member.next, typeof(pos), member))
#else
#define list_for_each_entry(pos, head, member)              \
  for (pos = list_entry_ptr((head)->next, typeof(pos), member); \
       &pos->member != (head);                              \
       pos = list_entry_ptr(pos->member.next, typeof(pos), member))
#endif
/**
 * list_for_each_entry_safe - iterate over list of given type safe against
 * removal of list entry
 * @pos:    the type * to use as a loop counter.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#ifndef _MSC_VER
#define list_for_each_entry_safe(pos, n, head, member)        \
  for (pos = list_entry_ptr((head)->next, typeof(pos), member),  \
       n = list_entry_ptr(pos->member.next, typeof(pos), member); \
       &pos->member != (head);                                \
       pos = n, n = list_entry_ptr(n->member.next, typeof(n), member))

#else

template <class T>
struct TypeofHelper {
  typedef T Type;
};

#define list_for_each_entry_safe(pos, n, head, member)                        \
  for (pos =                                                                  \
           list_entry_ptr((head)->next, TypeofHelper<typeof(pos)>::Type, member), \
      n = list_entry_ptr(pos->member.next, TypeofHelper<typeof(pos)>::Type,       \
                     member);                                                 \
       &(pos->member) != (head); pos = n,                                     \
      n = list_entry_ptr(n->member.next, TypeofHelper<typeof(n)>::Type, member))
#endif

}  // namespace base

#endif
