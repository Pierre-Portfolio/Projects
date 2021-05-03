package cineclub.controleurs;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FormulaireRechercheBoutonRadio extends JPanel implements ActionListener {
	// Composants
	JButton rechercher ; 
	JTextField saisieHeure ; 
	JTextField saisieTitre ; 
	
	// Constructeur
	FormulaireRechercheBoutonRadio () {
		setLayout (new BorderLayout());
		
		// Ajout des boutons radio pour sélection affichage par titre ou par heure
		ButtonGroup group = new ButtonGroup();
		JRadioButton boutonTitre = new JRadioButton("titre");
		JRadioButton boutonHeure = new JRadioButton("heure");
		group.add(boutonTitre);
		group.add(boutonHeure);
		JPanel radioPanel = new JPanel(new GridLayout(1, 2));
        radioPanel.add(boutonTitre);
        radioPanel.add(boutonHeure);

		add (BorderLayout.NORTH, radioPanel);

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
		FormulaireRechercheBoutonRadio f = new FormulaireRechercheBoutonRadio ();
		
		// Ajouter le label dans un des conteneurs de la fenetre
		fenetre.getContentPane().add(f);
			
		// Afficher la fenetre
		fenetre.setVisible(true);
	}

	public void actionPerformed(ActionEvent arg0) {
		// Lancer la recherche 
		// ...
	}
}
