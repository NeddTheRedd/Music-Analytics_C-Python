/** @file listy.h
 *  @brief Function prototypes for the linked list.
 */
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define MAX_LINE_LEN 256

typedef struct {
    char* artist;
    char* title;
    int year;
    int popularity;
    float danceability;
    float energy;
} Song;

typedef struct {
    char sortBy[MAX_LINE_LEN];
    int display;
    char file[MAX_LINE_LEN];
} ParsedArgs;

/**
 * @brief An struct that represents a node in the linked list.
 */
typedef struct node_t {
    Song *song;
    struct node_t *next;
} node_t;

/**
 * Function protypes associated with a linked list.
 */
node_t *new_node(Song *song);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *add_inorder(node_t *, node_t *, const char *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void apply(node_t *, void (*fn)(node_t *, void *, char *, int *), void *arg, char *sortBy, int *display);

#endif
