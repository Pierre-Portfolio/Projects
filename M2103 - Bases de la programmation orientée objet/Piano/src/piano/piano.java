package piano;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.IOException;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

public class piano extends JPanel implements ActionListener,KeyListener   {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	// Déclarer les composants graphiques
	private	JButton tn1,tn2,tn3,tn4,tn5,tb1,tb2,tb3,tb4,tb5,tb6,tb7;
	private	JButton tbbg1,tbbd1,tbbg2,tbbd2,tbbg3,tbbd3,tbbg4,tbbd4,tbbg5,tbbd5;
	
	public piano() {

		JPanel paneltouche = new JPanel ();
		paneltouche.setPreferredSize(new Dimension(700, 200)); 
		
		
		paneltouche.setLayout(new GridLayout(1,12));
		
		JPanel paneltouche1 = new JPanel (); 
		paneltouche1.setLayout(new GridLayout(2,1));
		
		JPanel paneltouche2 = new JPanel (); 
		paneltouche2.setLayout(new GridLayout(2,1));
		
		JPanel paneltouche3 = new JPanel (); 
		paneltouche3.setLayout(new GridLayout(2,1));
		
		JPanel paneltouche4 = new JPanel (); 
		paneltouche4.setLayout(new GridLayout(2,1));
		
		JPanel paneltouche5 = new JPanel (); 
		paneltouche5.setLayout(new GridLayout(2,1));
		
		JPanel paneltouchebas1 = new JPanel ();
		paneltouchebas1.setLayout(new GridLayout(1,2));
		JPanel paneltouchebas2 = new JPanel (); 
		paneltouchebas2.setLayout(new GridLayout(1,2));
		JPanel paneltouchebas3 = new JPanel (); 
		paneltouchebas3.setLayout(new GridLayout(1,2));
		JPanel paneltouchebas4 = new JPanel (); 
		paneltouchebas4.setLayout(new GridLayout(1,2));
		JPanel paneltouchebas5 = new JPanel (); 
		paneltouchebas5.setLayout(new GridLayout(1,2));
		
		
		tb1 = new JButton("tb1"); paneltouche.add(tb1);
		
		paneltouche.add(paneltouche1);
		tn1 = new JButton("tn1"); paneltouche1.add(tn1); 
		paneltouche1.add(paneltouchebas1);
		tbbg1 = new JButton("tbbg1"); paneltouchebas1.add(tbbg1);
		tbbd1 = new JButton("tbbd1"); paneltouchebas1.add(tbbd1);
		
		tb2 = new JButton("tb2"); paneltouche.add(tb2);
		
		paneltouche.add(paneltouche2);
		tn2 = new JButton("tn2"); paneltouche2.add(tn2);
		paneltouche2.add(paneltouchebas2);
		tbbg2 = new JButton("tbbg2"); paneltouchebas2.add(tbbg2);
		tbbd2 = new JButton("tbbd2"); paneltouchebas2.add(tbbd2);
		
		tb3 = new JButton("tb3"); paneltouche.add(tb3);
		tb4 = new JButton("tb4"); paneltouche.add(tb4);
		
		paneltouche.add(paneltouche3);
		tn3 = new JButton("tn3"); paneltouche3.add(tn3); 
		paneltouche3.add(paneltouchebas3);
		tbbg3 = new JButton("tbbg3"); paneltouchebas3.add(tbbg3);
		tbbd3 = new JButton("tbbd3"); paneltouchebas3.add(tbbd3);
		
		tb5 = new JButton("tb5"); paneltouche.add(tb5);
		
		paneltouche.add(paneltouche4);
		tn4 = new JButton("tn4"); paneltouche4.add(tn4); 
		paneltouche4.add(paneltouchebas4);
		tbbg4 = new JButton("tbbg4"); paneltouchebas4.add(tbbg4);
		tbbd4 = new JButton("tbbd4"); paneltouchebas4.add(tbbd4);
		
		tb6 = new JButton("tb6"); paneltouche.add(tb6);
		
		paneltouche.add(paneltouche5);
		tn5 = new JButton("tn5"); paneltouche5.add(tn5); 
		paneltouche5.add(paneltouchebas5);
		tbbg5 = new JButton("tbbg5"); paneltouchebas5.add(tbbg5);
		tbbd5 = new JButton("tbbd5"); paneltouchebas5.add(tbbd5);
		
		tb7 = new JButton("tb7"); paneltouche.add(tb7);
		
		tn1.setBackground(Color.black);
		tn2.setBackground(Color.black);
		tn3.setBackground(Color.black);
		tn4.setBackground(Color.black);
		tn5.setBackground(Color.black);
		
		tb1.setBackground(Color.white);
		tb2.setBackground(Color.white);
		tb3.setBackground(Color.white);
		tb4.setBackground(Color.white);
		tb5.setBackground(Color.white);
		tb6.setBackground(Color.white);
		tb7.setBackground(Color.white);
		
		tbbg1.setBackground(Color.white);
		tbbg2.setBackground(Color.white);
		tbbg3.setBackground(Color.white);
		tbbg4.setBackground(Color.white);
		tbbg5.setBackground(Color.white);
		tbbd1.setBackground(Color.white);
		tbbd2.setBackground(Color.white);
		tbbd3.setBackground(Color.white);
		tbbd4.setBackground(Color.white);
		tbbd5.setBackground(Color.white);
		
		tn1.addActionListener(this);
		tn2.addActionListener(this);
		tb1.addActionListener(this);
		tb2.addActionListener(this);
		tb3.addActionListener(this);
		tb4.addActionListener(this);
		tb5.addActionListener(this);
		tb6.addActionListener(this);
		tb7.addActionListener(this);
		addKeyListener(this);
		add(paneltouche);
		paneltouche.setFocusable(true);
		paneltouche.requestFocusInWindow();
		
		paneltouche1.setFocusable(true);
		paneltouche1.requestFocusInWindow();
		}
	
	
	
	public static void main(String args[]) {
		// Creer une fenetre
		JFrame f = new JFrame ("Piano By Pierre Pour Adele");

		// Ajouter a la fenetre la calculatrice
		piano c = new piano (); 
		f.getContentPane().add(c);
		
		// Afficher la fenetre
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setSize(600, 300);
		f.setVisible(true);
	}

	public void lancerson(String a) {
		AudioInputStream audioIn = null;
		try {
			audioIn = AudioSystem.getAudioInputStream(new File("C:\\Users\\pierre\\Music\\note\\blanche\\" + a).getAbsoluteFile());
		} catch (UnsupportedAudioFileException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Clip lala = null;
		try {
			lala = AudioSystem.getClip();
		} catch (LineUnavailableException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			lala.open(audioIn);
		} catch (LineUnavailableException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		lala.start();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		   String name = arg0.getActionCommand();
		   String a;
		   
		   if(name.equals("tb1")) {
			   a = "do.wav";
			   lancerson(a);	
		   }
		   
		   if(name.equals("tb2")) {
			   a = "re.wav";
			   lancerson(a);	
		   }
		   
		   if(name.equals("tb3")) {
			   a = "mi.wav";
			   lancerson(a);	
		   }
		   
		   if(name.equals("tb4")) {
			   a = "fa.wav";
			   lancerson(a);	
		   }
		   
		   if(name.equals("tb5")) {
			   a = "sol.wav";
			   lancerson(a);	
		   }
		   
		   if(name.equals("tb6")) {
			   a = "la.wav";
			   lancerson(a);	
		   }
		   
		   if(name.equals("tb7")) {
			   a = "si.wav";
			   lancerson(a);	
		   }
	}
	
    public void keyPressed(KeyEvent e) {
    	System.out.println("autre");
    }



	@Override
	public void keyReleased(KeyEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("autre1");
	}



	@Override
	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub
    	String a;
    	System.out.println("var");
    	if (arg0.getKeyChar() == 'a') {
    		System.out.println("if");
			   a = "do.wav";
			   lancerson(a);
    	}
	}
}
