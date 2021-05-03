package cineclub.modeles;

import java.util.ArrayList;

public interface InterfaceModeleSeances {
	void ajouterSeance (ModeleSeance s);
	ArrayList <ModeleSeance> rechercheSeance (String titreFilm);
	ArrayList <ModeleSeance> rechercheSeance (int heureSeance);
}
