package cineclub.vues;

import java.awt.GridLayout;
import java.sql.Date;
import javax.swing.*;
import cineclub.modeles.ModeleFilm;
import cineclub.modeles.ModeleSeance;

public class VueSeanceLabels extends JPanel {
	ModeleSeance s ; 

	public VueSeanceLabels(ModeleSeance s) {
		this.s = s ; 
	
		// Créer les composants
		VueFilmLabels vueFilm = new VueFilmLabels (s.getModeleFilm());
		JLabel heure = new JLabel (""+s.getHeure()+":00");
			
		// Ajouter les composants
		GridLayout gl = new GridLayout (2, 1);
		setLayout (gl);
		add (heure); 
		add (vueFilm);
	}

	public static void main(String[] args) {
		// Créer un modèle de film et un modele de seance pour ce film 
		ModeleFilm m = new ModeleFilm ("Gravity", 2013, "Gravity.jpg");
		ModeleSeance s = new ModeleSeance (m, 19);
		
		// Creer une fenetre
		JFrame fenetre = new JFrame ("VueSeanceLabels");
		fenetre.setSize (300, 300);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			
		// Creer une vue
		VueSeanceLabels v = new VueSeanceLabels (s);
		
		// Ajouter la vue dans un des conteneurs de la fenetre
		fenetre.getContentPane().add(v);
			
		// Afficher la fenetre
		fenetre.setVisible(true);
	}
}
