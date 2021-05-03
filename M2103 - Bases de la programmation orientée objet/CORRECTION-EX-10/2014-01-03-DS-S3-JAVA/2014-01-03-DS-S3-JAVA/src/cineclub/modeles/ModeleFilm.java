package cineclub.modeles;

public class ModeleFilm {

	private String titre ; 
	private int annee ; 
	private String nomImageAffiche ;
	
	public ModeleFilm(String titre, int annee, String nomImageAffiche) {
		this.titre = titre;
		this.annee = annee;
		this.nomImageAffiche = nomImageAffiche;
	}

	public String getTitre() {
		return titre;
	}

	public void setTitre(String titre) {
		this.titre = titre;
	}

	public int getAnnee() {
		return annee;
	}

	public void setAnnee(int annee) {
		this.annee = annee;
	}

	public String getNomImageAffiche() {
		return nomImageAffiche;
	}

	public void setNomImageAffiche(String nomImageAffiche) {
		this.nomImageAffiche = nomImageAffiche;
	}

	public static void main(String[] args) {
	}
}
