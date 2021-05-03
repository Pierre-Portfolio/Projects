public class TestInstanceOf {

    public static void main(String[] args) {
        Forme f ; 
        f = new Forme ();
        if (f instanceof Forme)
            System.out.println ("f instance de Forme ") ; 
        if (f instanceof Cercle)
            System.out.println ("f instance de Cercle ") ; 

        Forme c ; 
        c = new Cercle () ;  // Permis grace au polymorphisme !
        if (c instanceof Forme)
            System.out.println ("c instance de Forme") ; 
        if (c instanceof Cercle)
            System.out.println ("c instance de Cercle ") ; 
    }
}