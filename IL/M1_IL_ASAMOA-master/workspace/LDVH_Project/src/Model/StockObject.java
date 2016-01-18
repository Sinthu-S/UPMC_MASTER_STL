package Model;

import java.util.ArrayList;
/**
 * Cette classe représente les classes qui ont une liste d'objet comme les Enchainements et les Sections.
 * @author fred
 *
 */
public abstract class StockObject<T>  extends IdentifierIten{
	
	protected ArrayList<T> listObjets;
	
	
	public StockObject() {
		super();
		this.listObjets = new ArrayList<T>();
	}

	public void removeAllObject(){
		listObjets.clear();
	}
	
	public void addObject(T obj){
		listObjets.add(obj);
	}
	
	/**
	 * Supprime un ou des objet de la liste des Objet
	 * @param obj
	 */
	public void removeObject(Object obj){
		Objet.removeObjet((ArrayList<Objet>) listObjets, obj);
	}
	/**
	 * Test si un objet est dans la liste des objets
	 * @param obj
	 * @return
	 */
	public boolean objectIsHere(Object obj){
		return Objet.exist((ArrayList<Objet>) listObjets, obj);
	}
	/**
	 * Retourne la liste des objets.
	 * @return
	 */
	public ArrayList<T> objetsRequired(){
		return listObjets;
	}
}
