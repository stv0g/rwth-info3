#ifndef LAZYAKTION_H_
#define LAZYAKTION_H_

#include <list>

using namespace std;

// Oberklasse LazyAktion
template<class T> class LazyAktion {

public:
	LazyAktion(list<T> *ptLazyListe) : p_ptLazyListe(ptLazyListe) { }
	virtual ~LazyAktion() { }
	virtual void vAusfuehren() = 0;

protected:
	list<T> *p_ptLazyListe; // Zeiger auf p_ListeObjekte auf die die Aktionen angewendet werden sollen
};

// LazyPushFront
template<class T> class LazyPushFront : public LazyAktion<T> {

public:
	LazyPushFront(const T &einObjekt, list<T> *eineListe) :
		LazyAktion<T> (eineListe),
		p_tObjekt(einObjekt)
	{ }

	virtual ~LazyPushFront() { }

	void vAusfuehren() {
		p_ptLazyListe->push_front(p_tObjekt);
	}

private:
	//using LazyAktion<T>::p_ptLazyListe;
	T p_tObjekt;
};

// LazyPushBack
template<class T> class LazyPushBack : public LazyAktion<T> {

public:
	LazyPushBack(const T &einObjekt, list<T> *eineListe) :
		LazyAktion<T> (eineListe),
		p_tObjekt(einObjekt)
	{ }

	virtual ~LazyPushBack() { }

	void vAusfuehren() {
		p_ptLazyListe->push_back(p_tObjekt);
	}

private:
	//using LazyAktion<T>::p_ptLazyListe; // für gcc notwendig
	T p_tObjekt;
};

template <class T> class LazyErase : public LazyAktion<T> {
	// typedef für iterator
	typedef typename list<T>::iterator iterator;
	typedef typename list<T>::const_iterator const_iterator;

public:
	LazyErase(const iterator &itObjekt, list<T> *eineListe) :
			LazyAktion<T> (eineListe),
			p_itObjekt(itObjekt)
	{ }

	virtual ~LazyErase() { }

	void vAusfuehren() {
		p_ptLazyListe->erase(p_itObjekt);
	}

private:
	//using LazyAktion<T>::p_ptLazyListe; // für gcc notwendig
	iterator p_itObjekt; // bei erase Iterator speichern
};

#endif /* LAZYAKTION_H_ */
