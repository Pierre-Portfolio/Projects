class Cercle extends Forme {
    int rayon ;

	void afficher () {
        System.out.println ("x = " + x + " , y = " + y + ", couleur = " + couleur + 
        		" rayon = " + rayon);
    }
	
	
	
	
	
	
	
	
	
	
	
	
	
	void agrandir (int facteur) {
		rayon = rayon * facteur ;
	}
}