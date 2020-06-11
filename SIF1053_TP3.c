/*************************************************************************************************************
    *   SIF1053_TP3.c                  Auteur: Courteau, Yves                                           *
    *                                                                                                   *
    *   SIF1053, TP3                                                                                    *
    *                                                                                                   *
    *   Programme qui prend une image .raw en entrer et fait une encryption selon une clef de 8 bits.   *
    *   Trois parcours different sont dispobible afin de faire l'encryption (ils sont ausssi			* 
	* 	chronometre)...	 Ensuite le programme produit une nouvelle image raw en sortie avec la version	*
	*	de l'image encrypte...															                *
	*																									*
*************************************************************************************************************/

#include "fonction_tp.h"

int main(void)
{
	unsigned long duration;
	UCHAR nomImageIn[STRLEN], nomImageOut[STRLEN], largeur[INTLEN], hauteur[INTLEN], c[INTLEN], parcour[INTLEN], *endptr;
	int l, h, cle, len, p;
	bool vTpeFich;

	/*////////////////////////////////////////////////////////////////
		DEMANDE A L'UTILISATEUR : NOM INPUT, LARGEUR & HAUTEUR
	*/
	do
	{
		printf("Nom du fichier image portant l'extension 'raw': ");
		fgets(nomImageIn, STRLEN, stdin);
		len = strlen(nomImageIn);
		if (nomImageIn[len - 1] == '\n')
			nomImageIn[len - 1] = 0;

		vTpeFich = verifTypeFichier(nomImageIn);
		if (vTpeFich == false)
			printf("\n\nLe fichier doit avoir l'extention .raw\n\n");
	} while (vTpeFich == false);

	printf("Largeur: ");
	fgets(largeur, INTLEN, stdin);
	l = strtol(largeur, &endptr, INTLEN);

	printf("Hauteur: ");
	fgets(hauteur, INTLEN, stdin);
	h = strtol(hauteur, &endptr, INTLEN);

	IMAGE* im = lire_image(nomImageIn, l, h);

	/*////////////////////////////////////////////////////////////////
		DEMANDE A L'UTILISATEUR NOM OUTPUT
	*/

	do{
		printf("Nom de fichier image pour encryption: ");
		fgets(nomImageOut, STRLEN, stdin);
		len = strlen(nomImageOut);
		if(nomImageOut[len-1] == '\n')
			nomImageOut[len-1] = 0;

		vTpeFich = verifTypeFichier(nomImageOut);

		if(vTpeFich == false || strcmp(nomImageIn, nomImageOut) == 0)
			printf("\n\nLe fichier doit avoir l'extention .raw et le nom doit etre different du nom de fichier en entrer.\n\n");
	}while(vTpeFich == false || strcmp(nomImageIn, nomImageOut) == 0);

	/*////////////////////////////////////////////////////////////////
		DEMANDE A L'UTILISATEUR : VALEUR DE LA CLE D'ENCRYPTION
	*/

	do{
		printf("Valeur de cle d'encryption desirer: ");
		fgets(c, INTLEN, stdin);
		cle = strtol(c, &endptr, INTLEN);
		if(cle < CLE_MIN || cle > CLE_MAX)
			printf("\n\nChoix invalide, la cle doit etre entre %d et %d\n\n", CLE_MIN, CLE_MAX);
	}while(cle < CLE_MIN || cle > CLE_MAX);
	
	/*////////////////////////////////////////////////////////////////
		DEMANDE A L'UTILISATEUR : PARCOURS
	*/

	do
	{
		printf("\nQuel parcours?\n0: Sans positionnement spatial\n1: Positionnement spacial par rangees\n2: Positionnement spacial par colonnes\n\nVotre choix: ");
		fgets(parcour, INTLEN, stdin);
		p = strtol(parcour, &endptr, INTLEN);
		if(p < PARCOUR_MIN || p > PARCOUR_MAX)
			printf("\n\nChoix invalide\n\n");
	} while (p < PARCOUR_MIN || p > PARCOUR_MAX);

	/*////////////////////////////////////////////////////////////////
		ENCRYPTION AVEC CHRONOMETETRAGE & ECRITURE SUR IMAGE DE SORTIE
	*/

	_ftime(&debut);
	crypter_decrypter(im, cle, p);
	_ftime(&fin);

	duration = ((unsigned long)fin.time * 1000L + (unsigned long)fin.millitm) - ((unsigned long)debut.time * 1000L + (unsigned long)debut.millitm);
	printf("\n Duration: %d msec\n", duration);


	ecrire_image(im, nomImageOut);

	free(im->image);
	free(im);

	printf("\nL'image encrypter %s se trouve dans le dossier du programme.\n\n", nomImageOut);

	return EXIT_SUCCESS;
}