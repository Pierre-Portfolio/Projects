package methodes;
public class Dessin {
	public static void main (String args[]) {

		// Créer une forme et un cercle
		Forme f = new Forme (); f.x = 10 ; 
		Cercle c = new Cercle (); c.rayon = 5 ; 

		// Afficher leurs attributs
		System.out.println (f.x + "," + f.y + "," + f.couleur);
		System.out.println (c.x + "," + c.y + "," + c.couleur + "," + c.rayon);

		c.agrandir(2); // 2

		//f.agrandir(2); // Erreur de compilation

		System.out.println (f.x + "," + f.y + "," + f.couleur);
		System.out.println (c.x + "," + c.y + "," + c.couleur + "," + c.rayon);
	}
}
