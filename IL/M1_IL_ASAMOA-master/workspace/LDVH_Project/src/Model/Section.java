package Model;

import java.util.ArrayList;

public class Section extends StockObject{

	private static int nbInstance =0;
	
	private String description;
	
	public Section(String description) {
		super();
		this.description = description;
	}
	
	public Section(String description, ArrayList<Objet> listDropItem) {
		this(description);
		listObjets = listDropItem;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}
}
