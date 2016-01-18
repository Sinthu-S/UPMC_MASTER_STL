package Model.TestModel;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import Model.Enchainement;
import Model.Objet;
import Model.Section;
/**
 * Ici on test sur les listes d'objets fonctionnent bien (ajout ,suppression , reconnaissance d'objet) .
 * @author fred
 *
 */
public class ObjetItemTest {


	/**
	 * On remet à 0 tous les ID entre chaque test.
	 */
	@Before
	public void reinitId(){
		Enchainement.resetId(Enchainement.class);
		Objet.resetId(Objet.class);
		Section.resetId(Section.class);
	}

	//===================================Test sur la classe Enchainement=================================================
	/**
	 * Test pour savoir si les objets sont corréctement ajoutés et détéctés dans la liste.
	 */
	@Test
	public void testEnchainementPresence() {
		Enchainement e1 = new Enchainement(null, null);

		//===== Les objets=====
		Objet o1 = new Objet("Epée"); // id = 0
		Objet o2 = new Objet("Lance");
		Objet o3 = new Objet("Casque");
		Objet o4 = new Objet("Epée"); // id = 3
		Objet o5 = new Objet("Fake");

		e1.addObject(o1);
		e1.addObject(o2);
		e1.addObject(o3);
		e1.addObject(o4);
		// pas d'ajout de l'objet o5

		// Utilisation de la référence de l'objet 
		boolean res1 = e1.objectIsHere(o1);
		boolean res2 = e1.objectIsHere(o2);
		boolean res3 = e1.objectIsHere(o3);
		boolean res4 = e1.objectIsHere(o4);
		boolean res5 = !e1.objectIsHere(o5); // cet objet n'est pas présent

		// Utilisation de l'id de l'objet
		boolean res6 = e1.objectIsHere(0);
		boolean res7 = e1.objectIsHere(1);
		boolean res8 = e1.objectIsHere(2);
		boolean res9 = e1.objectIsHere(3);
		boolean res10 = !e1.objectIsHere(4); // cet objet n'est pas présent


		// Utilisation du nom de l'objet		
		boolean res11 = e1.objectIsHere("Epée");
		boolean res12 = e1.objectIsHere("Lance");
		boolean res13 = e1.objectIsHere("Casque");
		boolean res14 = !e1.objectIsHere("Fake"); // cet objet n'est pas présent

		assertTrue(res1&&res2&&res3&&res4&&res5&&res6&&res7&&res8&&res9&&res10&&res11&&res12&&res13&&res14);
	}
	/**
	 * Test si la fonction "removeAllObject" fonctionne bien 
	 */
	@Test
	public void testEnchainementRemoveAll(){
		Enchainement e1 = new Enchainement(null, null);

		//===== Les objets=====
		Objet o1 = new Objet("Epée"); // id = 0
		Objet o2 = new Objet("Lance");
		Objet o3 = new Objet("Casque");
		Objet o4 = new Objet("Epée"); // id = 3
		Objet o5 = new Objet("Fake");

		e1.addObject(o1);
		e1.addObject(o2);
		e1.addObject(o3);
		e1.addObject(o4);
		// pas d'ajout de l'objet o5

		boolean res1 = (4==e1.objetsRequired().size());
		e1.removeAllObject();
		boolean res2 = (0==e1.objetsRequired().size());

		assertTrue(res1&&res2); 

	}
	/**
	 * Test si la fonction "removeObject" fonctionne bien.
	 * 
	 */
	@Test
	public void testEnchainementRemove(){
		Enchainement e1 = new Enchainement(null, null);

		//===== Les objets=====
		Objet o1 = new Objet("Epée"); // id = 0
		Objet o2 = new Objet("Lance");
		Objet o3 = new Objet("Casque");
		Objet o4 = new Objet("Epée"); // id = 3
		Objet o5 = new Objet("Fake");

		e1.addObject(o1);
		e1.addObject(o2);
		e1.addObject(o3);
		e1.addObject(o4);
		// pas d'ajout de l'objet o5

		boolean res1 = (4==e1.objetsRequired().size());
		e1.removeObject("Epée");  // on supprime les deux items "Epée"

		boolean res2 = (2==e1.objetsRequired().size()); // il ne reste que deux items
		e1.removeObject(2); // on supprime le "casque" ( id = 2 )

		boolean res3 = (1==e1.objetsRequired().size());
		e1.removeObject(o5); // item n'existe pas dans la liste

		boolean res4 = (1==e1.objetsRequired().size());
		e1.removeObject(o2); // on supprime la "Lance"
		boolean res5 = (0==e1.objetsRequired().size()); // la liste doit être vide à la fin

		assertTrue(res1&&res2&&res3&&res4&&res5);
	}
	//===============================================Test sur la classe Section================================================
	/**
	 * Test pour savoir si les objets sont corréctement ajoutés et détéctés dans la liste.
	 */
	@Test
	public void testSectionPresence() {
		Section s1 = new Section("bla bla");

		//===== Les objets=====
		Objet o1 = new Objet("Epée"); // id = 0
		Objet o2 = new Objet("Lance");
		Objet o3 = new Objet("Casque");
		Objet o4 = new Objet("Epée"); // id = 3
		Objet o5 = new Objet("Fake");

		s1.addObject(o1);
		s1.addObject(o2);
		s1.addObject(o3);
		s1.addObject(o4);
		// pas d'ajout de l'objet o5

		// Utilisation de la référence de l'objet 
		boolean res1 = s1.objectIsHere(o1);
		boolean res2 = s1.objectIsHere(o2);
		boolean res3 = s1.objectIsHere(o3);
		boolean res4 = s1.objectIsHere(o4);
		boolean res5 = !s1.objectIsHere(o5); // cet objet n'est pas présent

		// Utilisation de l'id de l'objet
		boolean res6 = s1.objectIsHere(0);
		boolean res7 = s1.objectIsHere(1);
		boolean res8 = s1.objectIsHere(2);
		boolean res9 = s1.objectIsHere(3);
		boolean res10 = !s1.objectIsHere(4); // cet objet n'est pas présent


		// Utilisation du nom de l'objet		
		boolean res11 = s1.objectIsHere("Epée");
		boolean res12 = s1.objectIsHere("Lance");
		boolean res13 = s1.objectIsHere("Casque");
		boolean res14 = !s1.objectIsHere("Fake"); // cet objet n'est pas présent

		assertTrue(res1&&res2&&res3&&res4&&res5&&res6&&res7&&res8&&res9&&res10&&res11&&res12&&res13&&res14);
	}
	
	/**
	 * Test si la fonction "removeAllObject" fonctionne bien 
	 */
	@Test
	public void testSectionRemoveAll(){
		Enchainement e1 = new Enchainement(null, null);

		//===== Les objets=====
		Objet o1 = new Objet("Epée"); // id = 0
		Objet o2 = new Objet("Lance");
		Objet o3 = new Objet("Casque");
		Objet o4 = new Objet("Epée"); // id = 3
		Objet o5 = new Objet("Fake");

		e1.addObject(o1);
		e1.addObject(o2);
		e1.addObject(o3);
		e1.addObject(o4);
		// pas d'ajout de l'objet o5

		boolean res1 = (4==e1.objetsRequired().size());
		e1.removeAllObject();
		boolean res2 = (0==e1.objetsRequired().size());

		assertTrue(res1&&res2); 

	}
	/**
	 * Test si la fonction "removeObject" fonctionne bien.
	 * 
	 */
	@Test
	public void testSectionRemove(){
		Section s1 = new Section("bla bla");

		//===== Les objets=====
		Objet o1 = new Objet("Epée"); // id = 0
		Objet o2 = new Objet("Lance");
		Objet o3 = new Objet("Casque");
		Objet o4 = new Objet("Epée"); // id = 3
		Objet o5 = new Objet("Fake");

		s1.addObject(o1);
		s1.addObject(o2);
		s1.addObject(o3);
		s1.addObject(o4);
		// pas d'ajout de l'objet o5

		boolean res1 = (4==s1.objetsRequired().size());
		s1.removeObject("Epée");  // on supprime les deux items "Epée"

		boolean res2 = (2==s1.objetsRequired().size()); // il ne reste que deux items
		s1.removeObject(2); // on supprime le "casque" ( id = 2 )

		boolean res3 = (1==s1.objetsRequired().size());
		s1.removeObject(o5); // item n'existe pas dans la liste

		boolean res4 = (1==s1.objetsRequired().size());
		s1.removeObject(o2); // on supprime la "Lance"
		boolean res5 = (0==s1.objetsRequired().size()); // la liste doit être vide à la fin

		assertTrue(res1&&res2&&res3&&res4&&res5);
	}
}
