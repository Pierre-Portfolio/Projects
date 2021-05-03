package calculatrice.independant;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class EcouteurCalculatrice implements ActionListener {
	CalculatriceTableauPanel panel ;

	public EcouteurCalculatrice(CalculatriceTableauPanel panel) {
		super();
		this.panel = panel;
	}

	public void actionPerformed(ActionEvent e) {
		// On se contente de concaténer dans le résultat les touches tapées
		
		// Récupérer la commande du bouton
		JButton b = (JButton) (e.getSource());
		String s = b.getActionCommand();
		
		// L'ajouter au label résultat
		JLabel res = panel.getResultat();
		res.setText(res.getText()+s);
	} 
}
