#include <iostream>
#include <ctime>
#include <cstdlib>

typedef struct eintrag {
	int key;
	struct eintrag* p_prev;
	struct eintrag* p_next;
} eintrag_t;

typedef struct {
	eintrag_t* p_head;
	eintrag_t* p_tail;
	eintrag_t* p_curr;
	int length;
} liste_t;

liste_t* createList() {
	liste_t* list = (liste_t*)malloc(sizeof(liste_t));
	list->length = 0;
	list->p_head = NULL;
	list->p_tail = NULL;
	list->p_curr = NULL;

	return list;
}

eintrag_t* createElement(int key) {
	eintrag_t* elem = (eintrag*)malloc(sizeof(eintrag_t));

	elem->key = key;
	elem->p_next = NULL;
	elem->p_prev = NULL;

	return elem;
}

void insert_element(liste_t* list, int key) {
	eintrag_t* _elem = createElement(key);
	list->p_curr = list->p_head;
	//falls Liste leer
	if (list->length == 0) {
		list->p_head = _elem;
		list->p_tail = _elem;
		list->p_curr = _elem + sizeof(eintrag_t*);
		list->length++;
		return;
	}
	//Falls vor Head eingefügt wird
	if (_elem->key < list->p_head->key) {
		_elem->p_next = list->p_head;
		list->p_head->p_prev = _elem;
		list->p_head = _elem;
		return;
	}
	//Falls nach Tail eingefügt wird
	if (_elem->key > list->p_tail->key) {
		_elem->p_prev = list->p_tail;
		list->p_tail->p_next = _elem;
		list->p_tail = _elem;
		return;
	}
	//Einfügestelle suchen
	while (list->p_curr != NULL) {
		if (_elem->key > list->p_curr->key&& _elem->key < list->p_curr->p_next->key) {
			eintrag_t* swap = list->p_curr->p_next;
			list->p_curr->p_next = _elem;
			_elem->p_prev = list->p_curr;
			_elem->p_next = swap;
			list->p_curr->p_next->p_prev = _elem;
			list->p_curr = NULL;
		}
		else {
			list->p_curr = list->p_curr->p_next;
		}
	}
}

void print_list(liste_t* list) {
	eintrag_t* temp = list->p_head;
	int i = 0;
	while (temp != NULL) {
		std::cout << "Index: " << i << " | Key: " << temp->key << std::endl;
		i++;
		temp = temp->p_next;
	}
	std::cout << "\n";
}

void menu() {
	std::cout << "1. Element einfügen" << std::endl <<
		"2. Liste ausgeben" << std::endl <<
		"3. Fülle Liste mit zufälligen Zahlen" << std::endl <<
		"4. Exit" << std::endl << std::endl << "Ihre Eingabe: ";
}

int main(int argc, char const* argv[]) {
	int menuSelector;
	int key;
	liste_t* list = createList();

	while (1) {
		menu();
		std::cin >> menuSelector;
		if (menuSelector == 1) {
			std::cout << "Geben Sie den Wert des Elements ein: ";
			std::cin >> key;
			insert_element(list, key);
		}
		else if (menuSelector == 2) {
			if (list->length > 0)
				print_list(list);
			else
				std::cout << "Keine Elemente vorhanden!\n\n";
		}
		else if (menuSelector == 3) {
			int size;
			std::cout << "Wie viele Zahlen?: \n";
			std::cin >> size;
			for (int i = 0; i < size; i++) {
				srand(clock());
				insert_element(list, (rand() % 1000) + 1); //Füllt Liste mit Zahlen zwischen 1-1000
			}
		}
		else if (menuSelector == 4) {
			break;
		}
	}
	return 0;
}