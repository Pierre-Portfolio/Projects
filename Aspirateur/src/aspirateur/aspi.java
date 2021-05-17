package aspirateur;

public class aspi {
	public static final int x = 10 ;  
	public static final int y = 10 ;
	public static final int xIni = 5;  
	public static final int yIni = 5;
	public static String instruction  = "DADADADAA";
	public static char orientation = 'N';
	
	/*public static int[] deplacement() {
		
		return [1,2];
	}*/
	public static void cheminAspi(String inst,int posX,int posY) {
		int xFinal= posX;
		int yFinal= posY;
		for (char c : inst.toCharArray()) {
			if(c == 'D') {
				switch(orientation) {
				  case 'N':
					orientation = 'E';
				    break;
				  case 'E':
					orientation = 'S';
				    break;
				  case 'S':
					orientation = 'W';
					break;
				  case 'W':
					orientation = 'N';
					break;
				  default:
					  System.out.println("Erreur lors du changement de deplacement");
				}				
			}else if(c == 'G') {
				switch(orientation) {
				  case 'N':
					orientation = 'W';
				    break;
				  case 'W':
					orientation = 'S';
				    break;
				  case 'S':
					orientation = 'E';
					break;
				  case 'E':
					orientation = 'N';
					break;
				  default:
					  System.out.println("Erreur lors du changement de deplacement");
				}	
			}			
			else{
				switch(orientation) {
				  case 'N':
					if (yFinal != y) {
						yFinal++;
					}else {
						System.out.println("Le robot essaye de rentrer dans un mur !");
					}
				    break;
				  case 'E':
					if (xFinal != x) {
						xFinal++;
					}else {
						System.out.println("Le robot essaye de rentrer dans un mur !");
					}
				    break;
				  case 'S':
					if (yFinal != y) {
						yFinal--;
					}else {
						System.out.println("Le robot essaye de rentrer dans un mur !");
					}
					break;
				  case 'W':
					if (xFinal != x) {
						xFinal--;
					}else {
						System.out.println("Le robot essaye de rentrer dans un mur !");
					}
					break;
				  default:
					  System.out.println("Erreur lors du changement de deplacement");
				}
			}
		}
		System.out.println("x="+ xFinal + " y=" + yFinal + " orientation=" + orientation);
	}
	
	public static void main(String[] args) {
		cheminAspi(instruction,xIni,yIni);
	}
}
