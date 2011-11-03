#ifndef LAZYLISTE_H_
#define LAZYLISTE_H_

#include <list>

#include "LazyAktion.h"

using namespace std;

template<class T> class LazyListe {

public:
	// typedef für Iterator
	typedef typename list<T>::iterator iterator;
	typedef typename list<T>::const_iterator const_iterator;

	// Konstruktor / Destruktor
	LazyListe() {
		bChanged = false;
	}

	virtual ~LazyListe() {
		if (bChanged) {
			// ggf. noch anstehende Aktionen löschen
			do {
				delete *(p_ListeAktionen.begin());
				p_ListeAktionen.pop_front();
			} while (p_ListeAktionen.size() > 0);
		}
	}

	// Lesefunktionen
	const_iterator begin() const {
		return p_ListeObjekte.begin();
	}
	const_iterator end() const {
		return p_ListeObjekte.end();
	}

	iterator begin() {
		return p_ListeObjekte.begin();
	}

	iterator end() {
		return p_ListeObjekte.end();
	}

	bool empty() const {
		return p_ListeObjekte.empty();
	}

	// Schreibfunktionen
	void push_back(const T einObjekt) {
		p_ListeAktionen.push_back(new LazyPushBack<T>(einObjekt, &p_ListeObjekte));
		bChanged = true;
	}

	void push_front(const T einObjekt) {
		p_ListeAktionen.push_back(new LazyPushFront<T>(einObjekt, &p_ListeObjekte));
		bChanged = true;
	}

	void erase(iterator itObjekt) {
		p_ListeAktionen.push_back(new LazyErase<T>(itObjekt, &p_ListeObjekte));
		bChanged = true;
	}

	// Änderungen auf Objektliste übertragen
	void vAktualisieren() {
		if (bChanged) {
			// ausstehende Aktionen durchfuehren
			typename list<LazyAktion<T> *>::const_iterator it; // TODO warum typename?!
			for (it = p_ListeAktionen.begin(); it != p_ListeAktionen.end(); it++) {
				cout << "führe aktion aus, noch " << p_ListeAktionen.size() << endl;
				// Aktion ausführen
				//LazyAktion<T> *pAktion = *it;
				//pAktion->vAusfuehren();

				(*it)->vAusfuehren();

				// Zeiger auf Action-Element löschen
				delete *it;
			}
			// Liste der Aktionen leeren
			p_ListeAktionen.clear();

			bChanged = false;
		}
	}

private:
	list<T> p_ListeObjekte;
	list<LazyAktion<T> *> p_ListeAktionen;
	bool bChanged;
};

#endif /* LAZYLISTE_H_ */
