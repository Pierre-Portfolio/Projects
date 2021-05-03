import java.util.Scanner;


public class TypesDeBase {

	public static void main(String[] args) {

		//-----------------------------------------------------
		// Déclarations de variables locales à la méthode main () : types de base qui existent en C
		//-----------------------------------------------------
		short s ; 	// taille : 2 octets
		int i ;     // taille : 4 octets
		long l ;    // taille : 8 octets

		float f ; 	// taille : 4 octets
		double d ; 	// taille : 8 octets
		char c ; // format Unicode sur 2 octets

		//-----------------------------------------------------
		// Déclarations de types de base qui n’existent pas en C
		//-----------------------------------------------------
		byte by ; 	// taille : 1 octet
		boolean b ; 
				
		//-----------------------------------------------------
		// Affectation de quelques valeurs
		//-----------------------------------------------------
		i = 0 ; 
		b = true ; 
		c = 'a' ;
			
		//-----------------------------------------------------
		// Affichages
		//-----------------------------------------------------
		System.out.print (i); 				// AFFICHE 0.
		System.out.println (i); 			// AFFICHE 0 ET VA A LA LIGNE.....
		System.out.println ("i vaut " + i); // AFFICHE i vaut 0
		System.out.printf ("affichage formaté : %3.2f", 100.678);  // 100,68.
		System.out.println (); 			// ALLER A LA LIGNE
		
		//-----------------------------------------------------
		// Lecture au clavier 
		//-----------------------------------------------------
		Scanner sc = new Scanner(System.in);    // Créer un objet instance de la classe Scanner
		
		System.out.println("Veuillez saisir un mot : ");
		
		String str = sc.nextLine();  // Appeler la méthode nextLine () sur l'objet pointé par sc
		
		
		System.out.println("Vous avez saisi : " + str); // AFFICHE Vous avez saisi : au revoir
		
		System.out.println("Veuillez saisir un entier : ");
		int j = sc.nextInt();
		System.out.println("Vous avez saisi le nombre : " + j); // Vous avez saisi le nombre : 20
		
		//-----------------------------------------------------
		// Déclaration de constantes et initialisations
		//-----------------------------------------------------
		final int N = 20 ; // Déclarer une constante ayant pour valeur 20
		
		final int M ;
		System.out.println("Veuillez saisir un entier : ");
		M = sc.nextInt();
		// N = 10 ; => erreur de compilation
		
		//-----------------------------------------------------
		// Conversions implicites
		//-----------------------------------------------------
		int k = 1000 ; 
		long lo ; 
		lo = k ; 
		
		//-----------------------------------------------------
		// Conversions explicites (cast)
		//-----------------------------------------------------
		i =  (int) 2.5 ;
		System.out.println ("valeur de (int) 2.5 : " + i);

		//-----------------------------------------------------
		// Gestion des erreurs en Java
		//-----------------------------------------------------
		
		// Diviser par zéro
		i = i / 0 ; 
		
		// Saisir un caractère alors qu'on attend un nombre
		
	}
}
