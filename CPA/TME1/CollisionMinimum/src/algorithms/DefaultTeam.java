package algorithms;

import java.awt.Point;
import java.util.ArrayList;


/***************************************************************
 * TME 1: calcul de diamètre et de cercle couvrant minimum.    *
 *   - Trouver deux points les plus éloignés d'un ensemble de  *
 *     points donné en entrée.                                 *
 *   - Couvrir l'ensemble de poitns donné en entrée par un     *
 *     cercle de rayon minimum.                                *
 *                                                             *
 * class Circle:                                               *
 *   - Circle(Point c, int r) constructs a new circle          *
 *     centered at c with radius r.                            *
 *   - Point getCenter() returns the center point.             *
 *   - int getRadius() returns the circle radius.              *
 *                                                             *
 * class Line:                                                 *
 *   - Line(Point p, Point q) constructs a new line            *
 *     starting at p ending at q.                              *
 *   - Point getP() returns one of the two end points.         *
 *   - Point getQ() returns the other end point.               *
 ***************************************************************/
import supportGUI.Circle;
import supportGUI.Line;

public class DefaultTeam {

	// calculDiametre: ArrayList<Point> --> Line
	//   renvoie une pair de points de la liste, de distance maximum.
	public Line calculDiametre(ArrayList<Point> points) {
		if (points.size()<3) {
			return null;
		}

		Point p=points.get(0);
		Point q=points.get(1);
		
		/*******************
		 * PARTIE A ECRIRE *
		 *******************/
		
		return new Line(p,q);
	}
	
	// calculCercleMin: ArrayList<Point> --> Circle
	//   renvoie un cercle couvrant tout point de la liste, de rayon minimum.
	public Circle calculCercleMin(ArrayList<Point> points) {
		if (points.isEmpty()) {
			return null;
		}
		
		Circle c = null;
		Point s= points.get((int) (Math.random()/points.size()));
		Point p = null, q = null;
		Point centre;
		
		int distance=0;
		for(int i =0; i< points.size(); i++){
			if(s.distance(points.get(i)) > distance)
				p=points.get(i);
		}
		
		for(int i =0; i< points.size(); i++){
			if(p.distance(points.get(i)) > distance)
				q=points.get(i);
		}
		
		centre = milieuSeg(p,q);
		c =new Circle(centre, (int) centre.distance(p) );
		
		points.remove(q);
		points.remove(p);
		
		while(points.size() > 0) {
			s = points.get((int) (Math.random()/points.size()));
			if(s.distance(c.getCenter()) > c.getRadius()){
				
			}else{
				points.remove(s);
			}
			
		}
		
		//Algo naif
		/*for(int i =0; i< points.size(); i++){
			for(int j =0; j< points.size(); j++){
				c= new Circle(milieuSeg(points.get(j), points.get(i)) , (int) (points.get(j).distance(points.get(i))/2));
				if(containsAll(c, points)){
					return c;
				}
			}
		}
		return c;
		 */
		
		
		
	}

	
	
	// public cercleCirconscrit
	
	public 
	
	
	public Point milieuSeg(Point p, Point q){
		return new Point((int)((p.getX()+q.getX())/2) , (int)((p.getY() + q.getY())/2));
	}
	

	
	

	public boolean containsAll(Circle c, ArrayList<Point> points){
		 
		for(int i =0; i< points.size(); i++){
			if(points.get(i).distance(c.getCenter()) > c.getRadius())
				return false;
		}
		return true;
	}
		
}
