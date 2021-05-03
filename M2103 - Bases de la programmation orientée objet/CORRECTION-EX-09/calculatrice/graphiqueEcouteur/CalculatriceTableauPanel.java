package calculatrice.graphiqueEcouteur;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

// Version avec une déclaration de JButton par bouton
public class CalculatriceTableauPanel extends JPanel implements ActionListener {
	
	final static int NB_BOUTONS = 16 ; 
	
	// Déclarer les composants graphiques
	final static String [] labels = {	
									"1", "2", "3", "+", 
									"4", "5", "6", "-", 
									"7", "8", "9", "x",
									"C/CE", "0", "=", "/"};
	private JButton [] boutons ; 
	private JLabel resultat ; 
	
	public CalculatriceTableauPanel () {
		// Créer le label pour afficher le résultat
		resultat = new JLabel ("0");
		resultat.setBackground(Color.black);
		resultat.setOpaque(true);
		resultat.setForeground (Color.green);
		resultat.setHorizontalTextPosition(JLabel.RIGHT);
		resultat.setFont(new Font("Courier",Font.BOLD,48));
		resultat.setPreferredSize(new Dimension(100,52));

		// Créer le tableau de boutons
		boutons = new JButton [NB_BOUTONS];
		
		// Mettre en page les boutons
		JPanel panelBoutons = new JPanel (); 
		panelBoutons.setLayout(new GridLayout(4,4));
				
		// Creer les boutons et les ajouter au panel de boutons
		for (int i = 0; i < labels.length; i++) {
			boutons [i] = new JButton (labels[i]);
			boutons [i].setActionCommand(labels[i]);
			panelBoutons.add(boutons [i]);
			
			// Ajouter l'écouteur à chaque bouton
			boutons [i].addActionListener(this);
			
			// Fixer la couleur
			switch (labels[i]) {
				case "C/CE":
				case "=":
				case "+":
				case "-" : 
				case "x":
				case "/": 
					boutons [i].setBorder(BorderFactory.createLineBorder(Color.red)); break ;
				default: boutons [i].setBorder(BorderFactory.createLineBorder(Color.blue)); 
			}
		}
		
		// Mettre en page le tout
		setLayout(new BorderLayout());
		add(resultat,BorderLayout.NORTH);
		add(panelBoutons,BorderLayout.CENTER);
	}
	
	public JLabel getResultat() {
		return resultat;
	}

	public void setResultat(JLabel resultat) {
		this.resultat = resultat;
	}

	public static void main(String args[]) {
		// Creer une fenetre
		JFrame f = new JFrame ("Calculatrice");

		// Ajouter a la fenetre la calculatrice
		CalculatriceTableauPanel c = new CalculatriceTableauPanel (); 
		f.getContentPane().add(c);
		
		// Afficher la fenetre
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setSize(300,300);
		f.setVisible(true);
	}

	public void actionPerformed(ActionEvent e) {
		// Récupérer la commande du bouton
		JButton b = (JButton) (e.getSource());
		String s = b.getActionCommand();
		
		// L'ajouter au label résultat
		resultat.setText(resultat.getText()+s);		
	}
}
