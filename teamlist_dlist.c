#include "teamlist.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação com lista duplamente encadeada.
struct node {
    Team *team;
    struct node *next;
    struct node *prev;
};

struct teamlist {
    struct node *first;
    struct node *last;
    int size;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    if (tl == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    tl->first = NULL;
    tl->last = NULL;
    tl->size = 0;
    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    struct node *node = malloc(sizeof(struct node));
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->team = t;
    node->prev = tl->last;
    node->next = NULL;

    if (tl->last != NULL)
        tl->last->next = node;
    else
        tl->first = node;

    tl->last = node;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    if (i < 0 || i >= tl->size)
        return NULL;
    struct node *node = tl->first;
    for (int j = 0; j < i; j++)
        node = node->next;
    return node->team;
}

void tl_free(TeamList *tl) {
    if (tl == NULL)
        return;
    struct node *node = tl->first;
    while (node != NULL) {
        struct node *next = node->next;
        team_free(node->team);
        free(node);
        node = next;
    }
    free(tl);
}
