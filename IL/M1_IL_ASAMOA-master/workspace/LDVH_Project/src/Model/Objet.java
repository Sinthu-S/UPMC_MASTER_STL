package Model;

import java.util.ArrayList;

public class Objet extends IdentifierIten {

	
	private static int nbInstance =0;
	
	private String name;

	public Objet(String name) {
		super();
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Objet other = (Objet) obj;
		if (id != other.id)
			return false;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}

	/*
	 * Permet de chercher un objet par son id, son nom ou une instance d'objet.
	 */
	private boolean isMatch(Object obj){
		if(obj instanceof String){
			String nameObject = (String) obj;
			return (this.name.equals(nameObject));
		}else if(obj instanceof Integer){
			Integer idObject = (Integer) obj;
			return (this.id == idObject);
		}else if (obj instanceof Objet){
			Objet other = (Objet) obj;
			return this.equals(other);
		}else{
			assert true : "Le type n'est pas supporté !";
		}
		return false;


	}


	/**
	 * Supprime un objet de la liste "list" par son id , son nom ou une instance d'objet
	 * @param list , list ciblé
	 * @param obj , Peut être de type int, String ou Objet
	 */
	public static void removeObjet(ArrayList<Objet> list, Object obj){
		ArrayList<Objet> listToRemove = new ArrayList<Objet>();
		for(Objet o : list){
			if(o.isMatch(obj))
				listToRemove.add(o);
		}
		list.removeAll(listToRemove);
	}
	/**
	 * Cette fonction permet de tester si un objet est présent dans la liste
	 * @param list , la liste à tester
	 * @param obj  , Peut être de type int, String ou Objet
	 * @return true si l'objet est dans la liste.
	 */
	public static boolean exist(ArrayList<Objet> list, Object obj){
		for(Objet o : list){
			if(o.isMatch(obj))
				return true;
		}
		return false;
	}

	@Override
	public String toString() {
		return "Objet [name=" + name + ", id=" + id + "]";
	}

	

}
