/*** LAZYLISTE.H ***/

#ifndef __LazyListe_h
#define __LazyListe_h

#include <list>
#include "LazyAktion.h"

template <class T>
class LazyListe
{
   public:
      // typedef fuer iterator
      typedef typename list<T>::iterator iterator;
      typedef typename list<T>::const_iterator const_iterator; 

      // Konstruktor / Destruktor
      LazyListe() { bChanged = false; }
      virtual ~LazyListe()
      {
         if (bChanged)
         {
            // ggf. noch anstehende Aktionen löschen
            do
            {
               delete *(p_ListeAktionen.begin());
               p_ListeAktionen.pop_front();
            }
            while (p_ListeAktionen.size() > 0);
         }
      }

      // Lesefunktionen
      const_iterator begin() const {return p_ListeObjekte.begin();}
      const_iterator end() const {...}
      iterator begin() {return p_ListeObjekte.begin();}
      iterator end() {...}
      bool empty() const {...}

      // Schreibfunktionen
      void push_back( const T einObjekt )
      {
      p_ListeAktionen.push_back(new LazyPushBack<T>(...));
      bChanged = true;
      return;
      }

      void push_front( const T einObjekt )
      {
      ...

      bChanged = true;
      return;
      }

      void erase( iterator itObjekt )
      {
      ...

      bChanged = true;
      return;
      }

      // Änderungen auf Objektliste übertragen
      void vAktualisieren()
      {
         list <LazyAktion<T>*>::const_iterator itL;

         if ( bChanged )
         {
	         // ausstehende Aktionen durchfuehren
	         for (itL=... )
	         {
	         // Aktion ausführen
		         ...
            // Zeiger auf Action-Element löschen
               ...
	         }
	         // Liste der Aktionen leeren
            p_ListeAktionen.clear();

	         bChanged = false;
         }
      }

   private:
      list<T>					p_ListeObjekte;
      list<LazyAktion<T>*>	p_ListeAktionen;
      bool						bChanged;
};

#endif