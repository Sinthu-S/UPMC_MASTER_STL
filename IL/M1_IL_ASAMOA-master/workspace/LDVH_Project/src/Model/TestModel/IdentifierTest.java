/**
 * 
 */
package Model.TestModel;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import Model.Enchainement;
import Model.IdentifierIten;
import Model.Objet;
import Model.Section;

/**
 * @author fred
 *Ici on test si les classes Enchainement,Objet et Section ont bien un ID unique et correct.
 */
public class IdentifierTest {

	/**
	 * On remet à 0 tous les ID entre chaque test.
	 */
	@Before
	public void reinitId(){
		Enchainement.resetId(Enchainement.class);
		Objet.resetId(Objet.class);
		Section.resetId(Section.class);
	}

	@Test
	public void testEnchainement() {
		IdentifierIten e1 = new Enchainement(null, null);
		IdentifierIten e2 = new Enchainement(null, null);
		IdentifierIten e3 = new Enchainement(null, null);
		assertTrue( (0==e1.getId()) && (1==e2.getId()) && (2==e3.getId()) );
	}

	@Test
	public void testObjet() {
		IdentifierIten o1 = new Objet("Item 1");
		IdentifierIten o2 = new Objet("Item 2");
		IdentifierIten o3 = new Objet("Item 3");

		assertTrue( (0==o1.getId()) && (1==o2.getId()) && (2==o3.getId()) );
	}

	@Test
	public void testSection() {
		IdentifierIten s1 = new Section("blabla 1");
		IdentifierIten s2 = new Section("blabla 2");
		IdentifierIten s3 = new Section("blabla 3");
		assertTrue( (0==s1.getId()) && (1==s2.getId()) && (2==s3.getId()) );
	}

	@Test
	public void testAll() {
		IdentifierIten e1 = new Enchainement(null, null);
		IdentifierIten e2 = new Enchainement(null, null);
		IdentifierIten e3 = new Enchainement(null, null);

		IdentifierIten o1 = new Objet("Item 1");
		IdentifierIten o2 = new Objet("Item 2");
		IdentifierIten o3 = new Objet("Item 3");

		IdentifierIten s1 = new Section("blabla 1");
		IdentifierIten s2 = new Section("blabla 2");
		IdentifierIten s3 = new Section("blabla 3");

		assertTrue( (0==e1.getId()) && (1==e2.getId()) && (2==e3.getId()) 
				&&(0==o1.getId()) && (1==o2.getId()) && (2==o3.getId()) 
				&&(0==s1.getId()) && (1==s2.getId()) && (2==s3.getId())) ;
	}

	@Test
	public void testAllV2() {
		Enchainement e1 = new Enchainement(null, null);
		Enchainement e2 = new Enchainement(null, null);
		Enchainement e3 = new Enchainement(null, null);

		Objet o1 = new Objet("Item 1");
		Objet o2 = new Objet("Item 2");
		Objet o3 = new Objet("Item 3");

		Section s1 = new Section("blabla 1");
		Section s2 = new Section("blabla 2");
		Section s3 = new Section("blabla 3");

		assertTrue( (0==e1.getId()) && (1==e2.getId()) && (2==e3.getId()) 
				&&(0==o1.getId()) && (1==o2.getId()) && (2==o3.getId()) 
				&&(0==s1.getId()) && (1==s2.getId()) && (2==s3.getId())) ;
	}
}
