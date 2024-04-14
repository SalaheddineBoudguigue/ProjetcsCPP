/** \brief Ce fichier doit contenir la déclaration de la classe vecteur
    Attention, elle ne doit contenir aucune implémentation de méthode / fonction
*/



#ifndef _VECTEUR_H
#define _VECTEUR_H

#include <iostream>

// Déclaration de la classe vecteur
class Vecteur {
private :
  // attributs
  int N;
  float initial_value; // this attri is not necessary but if removed all implemetation need to be altered
  float* data;

public :
  // prototypes des constructeurs et autres méthodes publiques
  // constructeur
  Vecteur(int N=3, float initial_value=0.0);
  // constructeur de copie
  Vecteur(const Vecteur & v);
  // opérateur d'affectation
  Vecteur & operator=(const Vecteur & v);
  // opérateur d'addition
  Vecteur operator+(const Vecteur & v);
  // accesseurs en lecture et écriture
  float get(int i) const;
  void set(int i, float value);
  // dimensions du vecteur
  unsigned int dimensions() const;
  // accesseur en lecture
  float operator[](int i) const;
  // accesseur en écriture
  float& operator[](int i);
  
  // destructeur
  ~Vecteur();

  private :
    // méthodes privées d'implémentation (si besoin)
    // copie d'un vecteur
    void copy(const Vecteur & v);
};

// Prototypes des fonctions

// afficher un vecteur dans un flux de sortie
void afficherVecteur(const Vecteur * v, std::ostream & out = std::cout);

// lire un vecteur depuis un flux d'entrée
Vecteur * lireVecteur(std::istream & in = std::cin);

// additionner deux vecteurs
Vecteur add(const Vecteur* v1, const Vecteur* v2);

float operator*(const Vecteur & v1, const Vecteur & v2);

// surcharge des opérateurs << et >>
std::ostream & operator<<(std::ostream & out, const Vecteur & valeur) ;
std::istream & operator>>(std::istream & in, Vecteur& valeur) ;

#endif
