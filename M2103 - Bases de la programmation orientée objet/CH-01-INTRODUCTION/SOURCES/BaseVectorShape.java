/*****************************************************
 * Beginning Java Game Programming, 2nd Edition
 * by Jonathan S. Harbour
 * Base vector shape class for polygonal shapes
 *****************************************************/

import java.awt.Shape;

public class BaseVectorShape {
    //variables
    private Shape shape;
    private boolean alive;
    private double x,y;
    private double velX, velY;
    private double moveAngle, faceAngle;

    //accessor methods
    public Shape getShape() { return shape; }
    public boolean isAlive() { return alive; }
    public double getX() { return x; }
    public double getY() { return y; }
    public double getVelX() { return velX; }
    public double getVelY() { return velY; }
    public double getMoveAngle() { return moveAngle; }
    public double getFaceAngle() { return faceAngle; }

    //mutator methods
    public void setShape(Shape shape) { this.shape = shape; }
    public void setAlive(boolean alive) { this.alive = alive; }
    public void setX(double x) { this.x = x; }
    public void incX(double i) { this.x += i; }
    public void setY(double y) { this.y = y; }
    public void incY(double i) { this.y += i; }
    public void setVelX(double velX) { this.velX = velX; }
    public void incVelX(double i) { this.velX += i; }
    public void setVelY(double velY) { this.velY = velY; }
    public void incVelY(double i) { this.velY += i; }
    public void setFaceAngle(double angle) { this.faceAngle = angle; }
    public void incFaceAngle(double i) { this.faceAngle += i; }
    public void setMoveAngle(double angle) { this.moveAngle = angle; }
    public void incMoveAngle(double i) { this.moveAngle += i; }

    //default constructor
    BaseVectorShape() {
        setShape(null);
        setAlive(false);
        setX(0.0);
        setY(0.0);
        setVelX(0.0);
        setVelY(0.0);
        setMoveAngle(0.0);
        setFaceAngle(0.0);
    }
}
