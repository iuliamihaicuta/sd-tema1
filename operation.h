// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#define uint unsigned int

void
shuffle_deck(doubly_linked_list_t *pack);

void
reverse_deck(doubly_linked_list_t *pack);

void
merge_decks(doubly_linked_list_t *pack);

void
deck_len(doubly_linked_list_t *pack);

void
free_pack(doubly_linked_list_t **pack);

void
split_deck(doubly_linked_list_t *pack);

void
sort_deck(doubly_linked_list_t *pack);

#endif