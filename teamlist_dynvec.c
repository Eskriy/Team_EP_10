#include "teamlist.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação com vetor dinâmico de ponteiros para Team.
struct teamlist {
    Team **items;
    int size;
    int capacity;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    if (tl == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    tl->size = 0;
    tl->capacity = 4;
    tl->items = malloc(tl->capacity * sizeof(Team *));
    if (tl->items == NULL) {
        free(tl);
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    if (tl->size == tl->capacity) {
        int new_capacity = tl->capacity * 2;
        Team **new_items = realloc(tl->items, new_capacity * sizeof(Team *));
        if (new_items == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        tl->items = new_items;
        tl->capacity = new_capacity;
    }
    tl->items[tl->size] = t;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    if (i < 0 || i >= tl->size)
        return NULL;
    return tl->items[i];
}

void tl_free(TeamList *tl) {
    if (tl == NULL)
        return;
    for (int i = 0; i < tl->size; i++)
        team_free(tl->items[i]);
    free(tl->items);
    free(tl);
}
