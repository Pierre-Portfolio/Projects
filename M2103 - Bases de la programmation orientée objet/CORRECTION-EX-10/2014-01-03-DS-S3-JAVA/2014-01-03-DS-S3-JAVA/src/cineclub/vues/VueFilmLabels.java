package cineclub.vues;

import java.awt.GridLayout;

import javax.swing.*;

import cineclub.modeles.ModeleFilm;

public class VueFilmLabels extends JPanel implements InterfaceVueFilm {

	private static final long serialVersionUID = 1L;
	ModeleFilm m ; 
	JLabel titre ; 
	JLabel annee ; 
	
	public VueFilmLabels(ModeleFilm m) {
		this.m = m ; 
	
		// Créer les composants
		titre = new JLabel (m.getTitre());
		annee = new JLabel (""+m.getAnnee());
		
		// Mise en page
		setLayout (new GridLayout (2, 2));
		
		// Ajouter les composants
		add (new JLabel ("Titre : "));
		add (titre); 
		add (new JLabel ("Annee : "));
		add (annee); 
	}

	public static void main(String[] args) {
		// Créer un modèle
		ModeleFilm m = new ModeleFilm ("Gravity", 2013, "Gravity.jpg");
		
		// Creer une fenetre
		JFrame fenetre = new JFrame ("VueFilmLabels");
		fenetre.setSize (300, 300);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			
		// Creer une vue
		VueFilmLabels v = new VueFilmLabels (m);
		
		// Ajouter le label dans un des conteneurs de la fenetre
		fenetre.getContentPane().add(v);
			
		// Afficher la fenetre
		fenetre.setVisible(true);
	}

	public void miseAJour() {
		titre.setText(m.getTitre());
		annee.setText(""+m.getAnnee());
	}
}
