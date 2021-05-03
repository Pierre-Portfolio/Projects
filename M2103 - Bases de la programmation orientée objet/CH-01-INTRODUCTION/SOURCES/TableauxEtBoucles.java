import java.util.Arrays;


public class TableauxEtBoucles {

	public static void main(String[] args) {

		//-----------------------------------------------------
		// Tableau de type de base
		//-----------------------------------------------------
		int t [] ; 	// DECLARATION d'une REFERENCE de type tableau
		t = new int [3];	// ALLOCATION d'une zone mŽmoire pour n entiers dans le TAS
		t[2] = 7;			// AFFECTATION d'une valeur ˆ une case du tableau
		System.out.println(t[2]); // ACCES / LECTURE de la valeur d'une case du tableau et affichage
		
		//-----------------------------------------------------
		// Parcours du tableau
		//-----------------------------------------------------

		// Avec une boucle et un boolŽen
		boolean fini = false ; 
		int i = 0 ; 
		System.out.println ("\n Parcours du tableau avec un boolŽen et une boucle while : ");
		while (! fini) {
			System.out.println (t[i]);
			i++ ; 
			fini = i == t.length ;
		}
		
		// Avec une boucle foreach
		System.out.println ("\n Parcours du tableau avec une boucle foreach : ");
		for (int valeur : t)
			System.out.println (valeur);
		
		
		
		
		
		// Copie d'un tableau 
		int [] t2 = t ; // RECOPIE JUSTE L'ADRESSE DU TABLEAU
		t2 [0] = 33 ; 
		
	
		
		// Affichage apr�s copie : ........................
		System.out.println ("\n Parcours du tableau t apr�s modification  t2 = t ; t2[0] = 33 : ");
		for (int valeur : t)
			System.out.println (valeur);

		// Initialiser un tableau lors de la dŽclaration
		double notes [] = {12, 8, 17.5, 2, 19};
		
		// Affichage avant tri 
		System.out.println ("\n Affichage avant tri : ");
		for (double valeur : notes)
			System.out.println (valeur);

		// Trier un tableau 
		Arrays.sort(notes);
		
		// Affichage apr�s tri 
		System.out.println ("\n Affichage apr�s tri : ");
		for (double valeur : notes)
			System.out.println (valeur);

		//-----------------------------------------------------
		// Exceptions
		//-----------------------------------------------------

		// DŽbordement du tableau 
		System.out.println (t[2]);
		
		// Oubli d'allouer le tableau
		int tab [];
		tab = null ;
		// ...
		tab[0] = 10 ; 		 
	} 
}
