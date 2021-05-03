/*****************************************************
 * Beginning Java Game Programming, 2nd Edition
 * by Jonathan S. Harbour
 * Ship class - polygonal shape of the player's ship
 *****************************************************/
import java.awt.Polygon;
import java.awt.Rectangle;

public class Ship extends BaseVectorShape {
    //define the ship polygon
    private int[] shipx = { -6, -3, 0, 3, 6, 0 };
    private int[] shipy = { 6, 7, 7, 7, 6, -7 };

    //bounding rectangle
    public Rectangle getBounds() {
        Rectangle r;
        r = new Rectangle((int)getX() - 6, (int) getY() - 6, 12,12);
        return r;
    }

    Ship() {
        setShape(new Polygon(shipx, shipy, shipx.length));
        setAlive(true);
    }
}
