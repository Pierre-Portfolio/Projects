package metho;

class Dessin {
	public static void main (String args[]) {

		// Cr�er une forme et un cercle
		Forme f = new Forme ();
		f.x = 10 ; f.y = 10 ; 
		Cercle c = new Cercle ();
		c.x = 20 ; c.y = 30 ; c.rayon = 50 ; 
		
		// Afficher leurs attributs avec un println
		System.out.println(f.x + " " + f.y);		
		System.out.println(c.x + " " + c.y + " " + c.rayon);		
		
		// Appeler la m�thode afficher sur une instance de la classe Forme 
		f.afficher();
		
		// Appeler la m�thode afficher sur une instance 
		// de la classe Cercle : 
		// Cette m�thode est HERITEE !
		c.afficher();
		
		// Appeler la m�thode agrandir
		c.agrandir(2); // 2

		// f.agrandir(2); // ERREUR DE COMPILATION : he method agrandir(int) is undefined for the type Forme
	
		// 
		Forme f2 ; 
		f2 = new Cercle ();
		((Cercle) f2).agrandir(2);
		
		// Object o = ((String) f2); ERREUR DE COMPILATION : String 
		// n'est pas dans la m�me branche de la hi�rarchie
		
		
		System.out.println (f.x + "," + f.y + "," + f.couleur);
		System.out.println (c.x + "," + c.y + "," + c.couleur + "," + c.rayon);

	}
}

