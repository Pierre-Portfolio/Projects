package cineclub.controleurs;

import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

import javax.swing.*;

import cineclub.modeles.InterfaceModeleSeances;
import cineclub.modeles.ModeleSeance;
import cineclub.modeles.ModeleSeances;


public class FormulaireRecherche extends JPanel implements ActionListener {
	// Composants
	JButton rechercher ; 
	JTextField saisieHeure ; 
	JTextField saisieTitre ; 
	InterfaceModeleSeances seances ;
	
	// Constructeur
	FormulaireRecherche (InterfaceModeleSeances seances) {
		this.seances = seances ; 
		
		setLayout (new BorderLayout());
		add (BorderLayout.NORTH, new JLabel ("Recherche d'une séance"));

		JPanel saisie = new JPanel ();
		saisie.setLayout(new GridLayout(2,2));
		saisie.add (new JLabel ("Heure"));
		
		saisieHeure = new JTextField (5);
		saisie.add (saisieHeure);

		saisie.add (new JLabel ("Titre"));

		saisieTitre = new JTextField (10);
		saisie.add (saisieTitre);
		
		add (BorderLayout.CENTER, saisie);
		
		rechercher = new JButton ("Rechercher");
		add (BorderLayout.SOUTH, rechercher);
		
		// Ajouter les écouteurs
		rechercher.addActionListener (this);
		saisieHeure.addActionListener (this);
		saisieTitre.addActionListener (this);
	}

	public static void main(String[] args) {
		// Creer une fenetre
		JFrame fenetre = new JFrame ("Recherche");
		fenetre.setSize (300, 300);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			
		// Creer un formulaire de recherche
		ModeleSeances seances = new ModeleSeances();
		FormulaireRecherche f = new FormulaireRecherche (seances);
		
		// Ajouter le label dans un des conteneurs de la fenetre
		fenetre.getContentPane().add(f);
			
		// Afficher la fenetre
		fenetre.setVisible(true);
	}

	public void actionPerformed(ActionEvent arg0) {
		// Lancer la recherche 
		if (arg0.getSource () == saisieTitre) {
			String titre = saisieTitre.getText ();
			ArrayList <ModeleSeance>  res = seances.rechercheSeance (titre);
		}
		// Faire de même pour le champ de texte
	}
}
