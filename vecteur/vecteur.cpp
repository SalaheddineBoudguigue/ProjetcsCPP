/** \brief Ce fichier doit contenir l'ensemble des implémentations
relatives à la classe vecteur et aux fonctionnalités la concernant */

#include <cassert>
#include <iostream>
#include "vecteur.h"

// Constructeur
Vecteur::Vecteur(int N, float initial_value) : N(N), initial_value(initial_value) {
  assert(N > 0);
  data = new float[N];
  for (int i = 0; i < N; i++) {
    data[i] = initial_value;
  }
    std::cout << "Vecteur de dimensions " << N << " initialisé avec la valeur " << initial_value << std::endl;
}

//Destructeur
Vecteur::~Vecteur() {
  delete[] data;
}

// Accesseur en lecture
float Vecteur::get(int i) const {
  assert(i >= 0 && i < N);
  return data[i];
}

// Accesseur en écriture
void Vecteur::set(int i, float value) {
  assert(i >= 0 && i < N);
  data[i] = value;
}

// Accesseur en lecture
unsigned int Vecteur::dimensions() const {
  return N;
}

// afficher un vecteur dans un flux de sortie
void afficherVecteur(const Vecteur * v, std::ostream & out){
    out << "Vecteur de dimensions " << v->dimensions() << " : ( ";
    for (unsigned int i = 0; i < v->dimensions(); i++) {
        out << v->get(i) << " ";
    }
    out << ")" << std::endl;
}

Vecteur* lireVecteur(std::istream & in){
    int N;
    in >> N ;

    Vecteur* v = new Vecteur(N);

    float value;
    for (int i = 0; i < N; i++) {
        in >> value;
        v->set(i, value);
    }

    // retourner un nouveau vecteur initialisés avec les valeurs lues 
    return v;
}

Vecteur add(const Vecteur* v1, const Vecteur* v2){
    // vérification des dimensionss
    assert(v1->dimensions() == v2->dimensions());

    // Initialisation du vecteur résultat
    Vecteur result(v1->dimensions());

    // Calcul de la somme
    for (unsigned int i = 0; i < v1->dimensions(); i++) {
        result.set(i, v1->get(i) + v2->get(i));
    }

    return result;
}

// Copie d'un vecteur
void Vecteur::copy(const Vecteur & v) {
  N = v.N;
  initial_value = v.initial_value;
  data = new float[N];
  for (int i = 0; i < N; i++) {
    data[i] = v.data[i];
  }
}

// Constructeur de copie
Vecteur::Vecteur(const Vecteur & v) {
  copy(v);
}

// Opérateur d'affectation
Vecteur & Vecteur::operator=(const Vecteur & v) {
  // vérification de l'auto-affectation
  if (this != &v) {
    delete[] data; // libérer la mémoire occupée par le vecteur courant
    copy(v);
  }
  // retourner l'objet lui-même
  return *this;
}

// Opérateur d'addition
Vecteur Vecteur::operator+(const Vecteur& v) {

  return add(this, &v);
}

// Produit scalaire
float operator*(const Vecteur & v1, const Vecteur & v2){
    // vérification des dimensionss
    assert(v1.dimensions() == v2.dimensions());

    // Initialisation du vecteur résultat
    float result = 0;

    // Calcul du produit scalaire
    for (unsigned int i = 0; i < v1.dimensions(); i++) {
        result += v1.get(i) * v2.get(i);
    }

    return result;
}

std::ostream & operator<<(std::ostream & out, const Vecteur & valeur){
  afficherVecteur(&valeur, out);
  return out;
}

std::istream & operator>>(std::istream &in, Vecteur &vecteur) {
    for (size_t i = 0; i < vecteur.dimensions(); ++i) {
        float value;
        in >> value;
        vecteur.set(i, value);
    }
    return in;
}

float Vecteur::operator[](int i) const {
  assert(i >= 0 && i < N);
  return data[i];
}

float& Vecteur::operator[](int i) {
  assert(i >= 0 && i < N);
  return data[i];
}
