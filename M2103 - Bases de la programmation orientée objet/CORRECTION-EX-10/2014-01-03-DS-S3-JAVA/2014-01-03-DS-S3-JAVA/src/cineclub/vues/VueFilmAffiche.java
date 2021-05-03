package cineclub.vues;

import java.awt.GridLayout;

import javax.swing.*;

import cineclub.modeles.ModeleFilm;

public class VueFilmAffiche extends JPanel implements InterfaceVueFilm {

	private static final long serialVersionUID = 1L;
	ModeleFilm m ; 
	JLabel affiche ;
	
	public VueFilmAffiche(ModeleFilm m) {
		this.m = m ; 
		
		// Ajouter les composants
		affiche = new JLabel(); 
		affiche.setIcon(new ImageIcon (m.getNomImageAffiche()));
		add (affiche);
	}

	public static void main(String[] args) {
		// Créer un modèle
		ModeleFilm m = new ModeleFilm ("Gravity", 2013, "Gravity.jpg");
		
		// Creer une fenetre
		JFrame fenetre = new JFrame ("VueFilmAffiche");
		fenetre.setSize (300, 300);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			
		// Creer une vue
		VueFilmAffiche v = new VueFilmAffiche (m);
		
		// Ajouter le label dans un des conteneurs de la fenetre
		fenetre.getContentPane().add(v);
			
		// Afficher la fenetre
		fenetre.setVisible(true);
	}

	public void miseAJour() {
		affiche.setIcon(new ImageIcon (m.getNomImageAffiche()));		
	}
}
