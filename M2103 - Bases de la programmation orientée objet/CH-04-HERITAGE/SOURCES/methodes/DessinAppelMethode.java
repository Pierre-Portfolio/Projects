package methodes;
public class DessinAppelMethode {
	public static void main(String[] args) {
		Forme f ; 
		f = new Cercle (); //=> AUTORISE : f PEUT PRENDRE PLUSIEURS FORMES
		f.afficher ();   // Qu’est-ce qui est affiché ? :; 
		((Cercle) f).agrandir(2);
	}
}
