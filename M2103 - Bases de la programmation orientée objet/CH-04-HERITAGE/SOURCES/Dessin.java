class Dessin {
    public static void main (String args[]) {
        // Cr�er une forme et un cercle
    	Forme f = new Forme();
    	f.x = 10 ; 
    	f.y = 20 ; 
    	
    	Cercle c = new Cercle (); 
    	c.x = 30 ; 
    	c.y = 50 ; 
    	c.rayon = 100 ; 
    	
        // Afficher leurs attributs avec un println
    	System.out.println("Affichage avec println : ");
    	System.out.println("Forme : " + f.x + " - " + f.y);
    	System.out.println("Cercle : " + c.x + " - " + c.y + "-" + c.rayon);
    	    	
        // Appeler la m�thode afficher sur une instance de la classe Forme 
    	System.out.println("Affichage avec l'appel de la m�thode afficher() : ");
    	f.afficher();

        // Appeler la m�thode afficher sur une instance de la classe Cercle : 
        // Cette m�thode est HERITEE !
    	// On peut appeler cette m�thode sur des instances des sous-classes
    	// de la classe Forme
    	c.afficher();
    }
}





