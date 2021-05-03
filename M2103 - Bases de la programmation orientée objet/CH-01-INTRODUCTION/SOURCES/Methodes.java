
public class Methodes {

	// L'ordre de declaration des methodes n'a pas d'importance
	
	//------------------------------------------------------------------
	// Declarer un nombre variable d'arguments
	//------------------------------------------------------------------
	static int somme (int ... valeurs) {
		int s = 0 ; 
		for (int i=0; i < valeurs.length ; i++)
			s += valeurs [i];
		return s ;
	}
	
	//------------------------------------------------------------------
	// Procedure tentant d'echanger 2 parametres entiers 
	// Resultat : 
	//------------------------------------------------------------------
	static void echange (int a, int b) {
		int aux = b ; 
		b = a ; 
		a = aux ; 
		System.out.println ("durant l'appel apres echange : a = " + a + ", b = " + b);

	}

	//------------------------------------------------------------------
	// Procedure tentant de modifier la case d'un tableau passe en parametre 
	// Resultat : 
	//------------------------------------------------------------------
	static void modifierTab (int t[]) {
		t[0] = 9 ;
	}
	
	static void affiche (int a) {
		System.out.println ("Entree dans affiche : a = " + a);
		a = 20 ;
		System.out.println ("Avant de sortir de affiche : a = " + a);
	}
	//------------------------------------------------------------------
	// Programme principal
	//------------------------------------------------------------------
	public static void main(String[] args) {

		int a ; 
		a = 10 ;
		System.out.println ("Avant appel : a = " + a);
		affiche (a);
		System.out.println ("Apres appel : a = " + a);
	
		
		//------------------------------------------------------------------
		// Nombre variable de parametres
		//------------------------------------------------------------------
		System.out.println (somme (1, 2, 3));
		System.out.println (somme (2, 8));
		System.out.println (somme ());

	
		//------------------------------------------------------------------
		// Appel de la procedure tentant d'echanger 2 parametres entiers
		//------------------------------------------------------------------
		int i = 1 ; 
		int j = 2 ; 
		System.out.println ("avant appel echange : i = " + i + ", j = " + j);
		echange (i, j);
		System.out.println ("apres appel echange : i = " + i + ", j = " + j);

		
		//------------------------------------------------------------------
		// Appel de la procedure tentant de modifier la case d'un tableau passe en parametre
		//------------------------------------------------------------------
		int t[] = {1, 2, 3};
		
		System.out.println ("\n Affichage avant appel : ");
		for (int valeur : t)
			System.out.println (valeur);
		
		modifierTab (t);
		
		System.out.println ("\n Affichage apres appel : ");
		for (int valeur : t)
			System.out.println (valeur);	
	}
}
