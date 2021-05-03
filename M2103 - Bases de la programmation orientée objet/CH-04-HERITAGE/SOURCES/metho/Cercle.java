package metho;

public class Cercle extends Forme {
	int rayon ;
	void afficher () {
		  //System.out.println ("x = " + x + " , y = " + y + 
		//		  ", couleur = " + couleur + ", rayon = " + rayon);
		super.afficher();
	}
	
	void agrandir (int coefficient) {
		rayon *= coefficient ;
	}
}
