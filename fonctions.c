/************************************************************************
    *   fonctions.c       Auteur: Courteau, Yves                *
    *                                                           *
    *   Les fonctions de lecture, encryption, ecriture d'image. *
    *   Aussi, une fonction pour verifier l'extension .raw      *
    *                                                           *
************************************************************************/

#include "fonction_tp.h"

//  lire_image [lit une image et la stock dans une structure]
//  INPUT   :   *nomFichier : pointeur sur le nom du fichier
//				l 			: largeur
//				h 			: hauteur
//  OUTPUT  :   im			: la structure image produite
IMAGE *lire_image(char *nomFichier, int l, int h)
{
	IMAGE *im;
	FILE *inputImg;

	im = (IMAGE*)malloc(sizeof(IMAGE));
	im -> largeur = l; 
	im -> hauteur = h; 
	im -> image = (UCHAR*) malloc(im -> hauteur * im -> largeur);

	inputImg = fopen(nomFichier, "rb");
	if (inputImg == NULL)
	{
		printf("\n\nUn probleme est subvenue a l'ouverture du fichier %s\n\n", nomFichier);
		exit(EXIT_FAILURE);
	}
	size_t fileSize = fread(im -> image, sizeof(UCHAR), im -> hauteur * im -> largeur, inputImg);
	if (fileSize != (im->largeur * im->hauteur))
	{
		printf("\n\nUn probleme est subvenu a la lecture du fichier %s\n\n", nomFichier);
		exit(EXIT_FAILURE);
	}

	fclose(inputImg);
	return(im);
}

//	crypter_decrypter [Fait l'encryption selon le parcour choisi]
//  INPUT   :   *im			: pointeur sur structure image
//				cle 		: cle d'encryption
//				p 			: parcour
//  OUTPUT  :   im			: la structure image encrypte
IMAGE *crypter_decrypter(IMAGE *im, int cle, int p)
{
	int L, H, m, n;

	L = im -> largeur;
	H = im -> hauteur;
	
	switch (p)
	{
	case 0: 
		for (m = 0; m < L * H; m++) //	Acces sans positionnement spatial
			im -> image[m] = im -> image[m] ^ cle;
		break;
	case 1:
		for (m = 0; m < H; m++) //	Acces avec positionnement spatial
			for (n = 0; n < L; n++) //	Parcours par rangee
				im -> image[m * L + n] = im -> image[m * L + n] ^ cle;
		break;
	case 2:
		for (n = 0; n < L; n++) //	Acces avec positionnement spatial
			for (m = 0; m < H; m++) //	Parcours par colonne
				im -> image[m * L + n] = im -> image[m * L + n] ^ cle;
		break;
	default:
		printf("\n\nUne erreur est subvenue.\n\n");
		exit(EXIT_FAILURE);
	}

	return(im);
}

//  ecrire_image [ecrit une structure image sur un fichier]
//  INPUT   :   *imageD		: pointeur sur structure image
//				*nomFichier : pointeur sur le nom fichier
//  OUTPUT  :   outputImg	: le fichier image produit
void ecrire_image(IMAGE *imageD, char *nomFichier)
{
	FILE* outputImg;

	outputImg = fopen(nomFichier, "wb");
	if (outputImg == NULL)
	{
		printf("\n\nUn probleme est subvenu a l'ecriture du fichier %s\n\n", nomFichier);
		exit(EXIT_FAILURE);
	}

	size_t fileSize = fwrite(imageD -> image, sizeof(UCHAR), imageD -> hauteur * imageD -> largeur, outputImg);
	if (fileSize != (imageD -> largeur * imageD -> hauteur))
	{
		printf("\n\nUn probleme est subvenu a l'ecriture du fichier %s\n\n", nomFichier);
		exit(EXIT_FAILURE);
	}

	fclose(outputImg);
}

//  crypter_decrypter [Fait l'encryption selon le parcour choisi]
//  INPUT   :   *aVerif		: nom du fichier a verifier 
//  OUTPUT  :   booleen		: vrai si le nom du fichier fini par .raw
bool verifTypeFichier(char *aVerif)
{
	int len;
	len = strlen(aVerif);
	if (aVerif[len - 1] == 'w' && aVerif[len-2] == 'a' && aVerif[len-3] == 'r' && aVerif[len-4] == '.')
	{
		return true;
	}
	
	return false;
}