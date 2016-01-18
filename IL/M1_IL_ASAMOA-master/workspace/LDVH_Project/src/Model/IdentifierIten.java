package Model;

import java.lang.reflect.Field;
/**
 * Cette classe représente les classes ayant un ID unique.
 * @author fred
 *
 */
public abstract class IdentifierIten {

	protected int id;

	public IdentifierIten()
	{
		super();
		Class<? extends IdentifierIten> him = this.getClass();
		try {
			Field nbI = him.getDeclaredField("nbInstance");
			nbI.setAccessible(true);
			int val = nbI.getInt(this);
			id = val;
			nbI.setInt(him, ++val);
			nbI.setAccessible(false);
			
		} catch (NoSuchFieldException e) {
			e.printStackTrace();
		} catch (SecurityException e) {
			e.printStackTrace();
		}catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		}
		
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	static public void resetId(Class<? extends IdentifierIten> obj){
		try {
			Field nbI = obj.getDeclaredField("nbInstance");
			nbI.setAccessible(true);
			nbI.setInt(obj, 0);
			nbI.setAccessible(false);

		} catch (NoSuchFieldException e) {			
			e.printStackTrace();
		} catch (SecurityException e) {			
			e.printStackTrace();
		}catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		}
	}
}
