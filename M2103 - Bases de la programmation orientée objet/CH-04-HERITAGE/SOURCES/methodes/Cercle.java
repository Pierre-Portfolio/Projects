package methodes;
class Cercle extends Forme {
    int rayon ;
    
    // La méthode afficher prend plusieurs formes (dans plusieurs classes)
    // elle est POLYMORPHE
    void afficher () {
        super.afficher();
    	System.out.println (", rayon " + rayon);
      }
        
	public String toString() {
		return super.toString() + "[rayon=" + rayon + "]";
	}


	void agrandir (int facteur) {
		rayon = rayon * facteur ;
	}
	
	public static void main (String args[]) {
		Cercle c = new Cercle ();
		c.x = 10 ; c.y=20 ; c.rayon = 40 ; 
		System.out.println(c);
	}
}










