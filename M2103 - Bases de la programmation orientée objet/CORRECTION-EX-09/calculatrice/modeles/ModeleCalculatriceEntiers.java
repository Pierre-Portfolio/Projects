package calculatrice.modeles;

/**
 * Modele de la calculatrice
 */
public class ModeleCalculatriceEntiers implements InterfaceModeleCalculatrice {
	private static final int STATE_EDIT   = 0;
	private static final int STATE_MUL    = 1;
	private static final int STATE_ADD    = 2;
	private static final int STATE_DIV    = 3;
	private static final int STATE_SUB    = 4;
	private static final int STATE_RES    = 5;

	private int value = 0;
	private int valueA = 0;	
	private int state = STATE_EDIT;

	public void toucheEntree(int touche){

			switch (touche){
				case TOUCHE_0 : type(); value = value*10 ;   display(); break ; 
				case TOUCHE_1 : type(); value = value*10+1 ; display(); break ;
				case TOUCHE_2 : type(); value = value*10+2 ; display(); break ;
				case TOUCHE_3 : type(); value = value*10+3 ; display(); break ;
				case TOUCHE_4 : type(); value = value*10+4 ; display(); break ;
				case TOUCHE_5 : type(); value = value*10+5 ; display(); break ;
				case TOUCHE_6 : type(); value = value*10+6 ; display(); break ;
				case TOUCHE_7 : type(); value = value*10+7 ; display(); break ;
				case TOUCHE_8 : type(); value = value*10+8 ; display(); break ;
				case TOUCHE_9 : type(); value = value*10+9 ; display(); break ;
	
				case TOUCHE_DIVIS : operate(); valueA = value ; value = 0; state = STATE_DIV; break ;
				case TOUCHE_MOINS : operate(); valueA = value ; value = 0; state = STATE_SUB; break ;
				case TOUCHE_MULTI : operate(); valueA = value ; value = 0; state = STATE_MUL; break ;
				case TOUCHE_PLUS  : operate(); valueA = value ; value = 0; state = STATE_ADD; break ;
	
				case TOUCHE_EGAL  : operate();  state = STATE_RES; valueA = value ; break ;
	
				case TOUCHE_CE  : valueA = 0 ; value = 0; state = STATE_EDIT; display();; break ;
			}
		}

		private void type() {
			switch (state){
				case STATE_RES : state = STATE_EDIT; value=0; valueA=0;  break;
			}
		}

		private boolean operate() {
			try {
				switch (state){
				case STATE_EDIT : break;
				case STATE_ADD : value = valueA + value ; display(); break;
				case STATE_SUB : value = valueA - value ; display(); break;
				case STATE_MUL : value = valueA * value ; display(); break;
				case STATE_DIV : value = valueA / value ; display(); break;
				case STATE_RES : value = valueA         ; display(); break;
				}
			} catch (Exception e){
				valueA = 0; value=0; 
				state = STATE_RES;
				display();
				return false;
			}
			
			return true;
		}

		private void display() {
			//System.out.println ("TRACE : " + value);
		}
		
		public double getValeur () {
			return value ;
		}
		
		public static void main (String args []) {
			ModeleCalculatriceEntiers modele = new ModeleCalculatriceEntiers();
			modele.toucheEntree(TOUCHE_2);
			modele.toucheEntree(TOUCHE_1);
			modele.toucheEntree(TOUCHE_MULTI);
			modele.toucheEntree(TOUCHE_3);
			modele.toucheEntree(TOUCHE_EGAL);	
			
			System.out.println("Resultat = " + modele.getValeur());
		}
	}
