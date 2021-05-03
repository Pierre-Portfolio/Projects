package cineclub.vues;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JTabbedPane;

import cineclub.modeles.ModeleFilm;

public class VuesFilmTabbedPane extends JTabbedPane implements InterfaceVueFilm {
	// Attributs
	VueFilmAffiche va ; 
	VueFilmLabels vl ; 
	
	// Constructeur
	VuesFilmTabbedPane (ModeleFilm m) {
		// Creer une vue labels et l'ajouter dans un onglet
		vl = new VueFilmLabels (m);
		addTab("Vue Labels", vl); 

		// Creer une vue affiche et l'ajouter dans un onglet
		va = new VueFilmAffiche (m);
		addTab("Vue Affiche", va); 	
	}
	
	// Mettre à jour les deux vues
	public void miseAJour() {
		va.miseAJour(); 
		vl.miseAJour(); 
	}
	
	public static void main(String[] args) {
		// Créer un modèle de film
		ModeleFilm m = new ModeleFilm ("Gravity", 2013, "Gravity.jpg");
		
		// Creer une fenetre
		JFrame fenetre = new JFrame ("Vues Film Onglets");
		fenetre.setSize (300, 300);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			
		// Creer une vue onglets
		VuesFilmTabbedPane v = new VuesFilmTabbedPane (m);
				
		// Ajouter la vue dans un des conteneurs de la fenetre
		fenetre.getContentPane().add(v);
			
		// Afficher la fenetre
		fenetre.setVisible(true);

	}

}
