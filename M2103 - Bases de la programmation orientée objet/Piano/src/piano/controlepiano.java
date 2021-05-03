package piano;

import javax.swing.JFrame;

public class controlepiano {
	public static void main(String args[]) {
		// Creer une fenetre
		JFrame f = new JFrame ("Piano By Pierre Pour Adele");

		// Ajouter a la fenetre la calculatrice
		piano c = new piano(); 
		f.getContentPane().add(c);
		
		// Afficher la fenetre
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setSize(1000, 300);
		f.setVisible(true);
	}
	
}
