package p2;

import p1.A;

public class B extends A {
	int z ; 
	void m () {
		setX(2) ; 
		y = 3 ; 
	}
	
	public static void main (String args[]) {
		B objetB = new B();
		objetB.setX(12) ;
	}
}

class D extends A {
	void m() {
		y = 3 ;
	}
}
