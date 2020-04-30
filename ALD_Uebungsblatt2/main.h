#pragma once

/* Datenstruktur eines Listenelements */
typedef struct eintrag {
	int key;
	struct eintrag* p_prev;
	struct eintrag* p_next;
} eintrag_t;

/* Datenstruktur mit Informationen ueber die Liste */
typedef struct {
	eintrag_t* p_head;
	eintrag_t* p_tail;
	eintrag_t* p_curr;
	int length;
} liste_t;

// Legt den Speicher f ̈ur ein Listenelement an,
//speichert den key-Wert im Element.
//Gibt einen Zeiger auf das neues Listenelement zuruck.
eintrag_t* create_element(int key);
//F ̈ugt ein Element sortiert in die Liste ein.
//Zuerst wird die Position gesucht, an der das Listenelement
//eingef ̈ugt werden soll.
//Es sind 3 M ̈oglichkeiten zu unterscheiden, am Anfang der Liste,
//mitten in der Liste oder am Ende der Liste.
//Anschließend wird das Element in die Liste eingefugt.
void insert_element(liste_t* liste, eintrag_t* p_insert);
//Gibt alle Listen-Elemente aus
void print_list(liste_t liste);
