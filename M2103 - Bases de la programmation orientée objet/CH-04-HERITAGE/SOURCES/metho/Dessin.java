package metho;

class Dessin {
	public static void main (String args[]) {

		// Créer une forme et un cercle
		Forme f = new Forme ();
		f.x = 10 ; f.y = 10 ; 
		Cercle c = new Cercle ();
		c.x = 20 ; c.y = 30 ; c.rayon = 50 ; 
		
		// Afficher leurs attributs avec un println
		System.out.println(f.x + " " + f.y);		
		System.out.println(c.x + " " + c.y + " " + c.rayon);		
		
		// Appeler la méthode afficher sur une instance de la classe Forme 
		f.afficher();
		
		// Appeler la méthode afficher sur une instance 
		// de la classe Cercle : 
		// Cette méthode est HERITEE !
		c.afficher();
		
		// Appeler la méthode agrandir
		c.agrandir(2); // 2

		// f.agrandir(2); // ERREUR DE COMPILATION : he method agrandir(int) is undefined for the type Forme
	
		// 
		Forme f2 ; 
		f2 = new Cercle ();
		((Cercle) f2).agrandir(2);
		
		// Object o = ((String) f2); ERREUR DE COMPILATION : String 
		// n'est pas dans la même branche de la hiérarchie
		
		
		System.out.println (f.x + "," + f.y + "," + f.couleur);
		System.out.println (c.x + "," + c.y + "," + c.couleur + "," + c.rayon);

	}
}

