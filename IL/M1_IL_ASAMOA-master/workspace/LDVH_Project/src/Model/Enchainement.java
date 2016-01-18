package Model;

import java.util.ArrayList;

public class Enchainement extends StockObject{

	private static int nbInstance =0;

	private Section start;
	private Section end;

	public Enchainement(Section start, Section end) {
		super();
		this.start = start;
		this.end = end;

	}

	public Enchainement(Section start, Section end, ArrayList<Objet> listObjetsRequired) {
		this(start,end);
		listObjets = listObjetsRequired;
	}

	public void changeSectionStart(Section start){
		this.start = start;
	}
	public void changeSectionEnd(Section end){
		this.end = end;
	}





}
