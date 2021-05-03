package piano;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.*;

// Version avec une déclaration de JButton par bouton
public class calculette extends JPanel {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	// Déclarer les composants graphiques
	private	JButton b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,ba,bm,bd,bs,be,bc,bp;
	private JLabel resultat ; 
	
	public calculette () {
		// Créer le label pour afficher le résultat
		resultat = new JLabel ("0");
		resultat.setBackground(Color.black);
		resultat.setOpaque(true);
		resultat.setForeground (Color.green);
		resultat.setHorizontalTextPosition(JLabel.RIGHT);
		resultat.setFont(new Font("Courier",Font.BOLD,48));
		resultat.setPreferredSize(new Dimension(100,52));
	
		// Mettre en page les boutons
		JPanel panelBoutons = new JPanel (); 
		panelBoutons.setLayout(new GridLayout(4,4));
		
		// Creer les boutons et les ajouter au panel de boutons
		b1 = new JButton("1"); panelBoutons.add(b1); 
		b2 = new JButton("2"); panelBoutons.add(b2); 
		b3 = new JButton("3"); panelBoutons.add(b3); 
		ba = new JButton("+"); panelBoutons.add(ba); 
		
		b4 = new JButton("4"); panelBoutons.add(b4); 
		b5 = new JButton("5"); panelBoutons.add(b5); 
		b6 = new JButton("6"); panelBoutons.add(b6); 
		bs = new JButton("-"); panelBoutons.add(bs); 
		
		b7 = new JButton("7"); panelBoutons.add(b7); 
		b8 = new JButton("8"); panelBoutons.add(b8); 
		b9 = new JButton("9"); panelBoutons.add(b9); 
		bm = new JButton("x"); panelBoutons.add(bm); 
		
		bc = new JButton("C/CE"); panelBoutons.add(bc); 
		b0 = new JButton("0"); panelBoutons.add(b0); 
		be = new JButton("="); panelBoutons.add(be); 
		bd = new JButton("/"); panelBoutons.add(bd); 
		
		// Fixer la couleur des boutons
		bc.setBorder(BorderFactory.createLineBorder(Color.red));
		be.setBorder(BorderFactory.createLineBorder(Color.red));
		bm.setBorder(BorderFactory.createLineBorder(Color.red));
		bd.setBorder(BorderFactory.createLineBorder(Color.red));
		bs.setBorder(BorderFactory.createLineBorder(Color.red));
		ba.setBorder(BorderFactory.createLineBorder(Color.red));
		bc.setForeground(Color.red);
		be.setBackground(Color.red);
		
		b0.setBorder(BorderFactory.createLineBorder(Color.blue));
		b1.setBorder(BorderFactory.createLineBorder(Color.blue)); 
		b2.setBorder(BorderFactory.createLineBorder(Color.blue));
		b3.setBorder(BorderFactory.createLineBorder(Color.blue));
		b4.setBorder(BorderFactory.createLineBorder(Color.blue));
		b5.setBorder(BorderFactory.createLineBorder(Color.blue));
		b6.setBorder(BorderFactory.createLineBorder(Color.blue));
		b7.setBorder(BorderFactory.createLineBorder(Color.blue));
		b8.setBorder(BorderFactory.createLineBorder(Color.blue));
		b9.setBorder(BorderFactory.createLineBorder(Color.blue));
		
		// Mettre en page le tout
		setLayout(new BorderLayout());
		add(resultat,BorderLayout.NORTH);
		add(panelBoutons,BorderLayout.CENTER);
	}
	
	public static void main(String args[]) {
		// Creer une fenetre
		JFrame f = new JFrame ("Calculatrice");

		// Ajouter a la fenetre la calculatrice
		calculette c = new calculette (); 
		f.getContentPane().add(c);
		
		// Afficher la fenetre
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setSize(300,300);
		f.setVisible(true);
	}
}
