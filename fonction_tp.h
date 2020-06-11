#ifndef __FONCTION_TP_H
#define __FONCTION_TP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Ignore le code d'erreur C4996, produit par les fonctions fopen, scanf et 
// fscanf sous Visual Studio Community...
#pragma warning(disable : 4996)


/**********************************************************/
/************Constantes & Structures***********************/
/**********************************************************/
#define STRLEN 80
#define INTLEN 10
#define CLE_MIN 0
#define CLE_MAX 255
#define PARCOUR_MIN 0
#define PARCOUR_MAX 2

typedef unsigned char UCHAR;

typedef struct IMAGERAW {
	int hauteur;
	int largeur;
	UCHAR* image;
}IMAGE;

struct _timeb debut, fin;


/**********************************************************/
/************Prototypes des fonctions**********************/
/**********************************************************/
IMAGE *lire_image(char *nomFichier, int l, int h);
IMAGE *crypter_decrypter(IMAGE *im, int cle, int p);
void ecrire_image(IMAGE *imageD, char *nomFichier);
bool verifTypeFichier(char *aVerif);

#endif