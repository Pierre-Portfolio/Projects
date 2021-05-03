package cineclub.modeles;

import java.util.Date;

public class ModeleSeance {
	private ModeleFilm modeleFilm ; 
	private int heure ;
	
	public ModeleFilm getModeleFilm() {
		return modeleFilm;
	}

	public void setModeleFilm(ModeleFilm m) {
		this.modeleFilm = m;
	}

	public int getHeure() {
		return heure;
	}

	public void setHeure(int heure) {
		this.heure = heure;
	}

	public ModeleSeance(ModeleFilm modeleFilm, int heure) {
		super();
		this.modeleFilm = modeleFilm;
		this.heure = heure;
	}
}
