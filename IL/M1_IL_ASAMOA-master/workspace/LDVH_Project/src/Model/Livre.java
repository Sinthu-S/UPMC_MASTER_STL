package Model;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 *  * Classe Livre qui représente un livre, un seul livre peut être chargé en même temps,
 *  d'où l'utilisation d'un pattern Singleton.
 * @author fred
 *
 */
public class Livre implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	static private Livre instance = null; // Varibale blobale du patern singleton

	private ArrayList<Enchainement> listEnchainements; // Liste de tout les Enchainements existants
	private ArrayList<Objet> listObjets; // Liste de tout les Objet existants
	private ArrayList<Section> listSections; // Liste de toutes les Sections existants
	private String name;
	/*
	 * Constructeur de la classe Livre en privé pour préserver le patern Singleton
	 */
	private Livre(String name){
		listEnchainements = new ArrayList<Enchainement>();
		listObjets = new ArrayList<Objet>();
		listSections = new ArrayList<Section>();
		this.name = name;
	}
	/**
	 * Créer un nouveau livre avec un nouveau nom.
	 */
	private static void createNewLivre(){
		//... 
		//interface graphique pour récupérer le nom du nouveau livre
		// ...
		String retour = JOptionPane.showInputDialog(null,"Nom du live : ", "Nouveau livre", JOptionPane.QUESTION_MESSAGE);
		if (retour!=null){
			instance = new Livre(retour);
		}
		//...
		// ici un update sur les interfaces graphiques 
		//..
	}
	/*
	 * Fonction qui permet de récupérer la seul instance de la classe livre.
	 */
	static public Livre getInstance(){
		if(instance == null){
			// on est en train de créer un nouveau livre.
			createNewLivre();
		}
		return instance;
	}

	//========================================Sauvegarde et Chargement=============================================

	//========Sauvegarde======
	/**
	 * Exportation d'un  livre par la sérialisation
	 * @param le nom du fichier à  charger (en convention {@link File})
	 * @param le livre à sauvegarder
	 * @throws IOException En cas de probléme d'ecriture dans ce fichier.
	 */
	private void sauver(String fileName, Livre livre)throws IOException {   
		
		FileOutputStream fos = new FileOutputStream(fileName);
		ObjectOutputStream oos = new ObjectOutputStream(fos);
		oos.writeObject(livre);
		fos.close();
	}

	/**
	 * Fonction qui aide l'utilisateur à choisir un chemin pour la sauvegarde du livre
	 * @throws IOException
	 */
	public void sauvegarderUnLivre() throws IOException 
	{
		if (instance==null){ 
			//on imagine une instance générale d’un livre qui utilise le paterne singleton 
			//( car on n’auras qu’un livre chargé en même temps.)
			JOptionPane.showMessageDialog(null, "Aucun livre n’a été chargé !", "Warnig", JOptionPane.WARNING_MESSAGE);
		}else{
			String fileName = JOptionPane
					.showInputDialog("Please enter a file name to save this book (extension .ldvh).");
			if(!fileName.isEmpty()){
				sauver(fileName, instance);
			}else{
				JOptionPane.showMessageDialog(null, "Incorrect path !", "Warnig", JOptionPane.WARNING_MESSAGE); 
			}
		}
	}

	//========Chargement======	
	/**
	 *  Chargement d'un livre par la sérialisation (à partir d'un fichier .ldvh)
	 * @param fileName : le chemin du fichier .ldvh
	 * @return une instance du livre chargé
	 * @throws IOException
	 */
	private Livre charger(String fileName) throws IOException {
		FileInputStream fis = new FileInputStream(fileName);
		ObjectInputStream ois = new ObjectInputStream(fis);
		try {
			Livre res= (Livre) ois.readObject();
			return res;
		} catch (ClassCastException e) {
			throw new IOException(
					"Le fichier n'est pas un LDVH.", e);
		} catch (ClassNotFoundException e) {
			throw new IOException(
					"JVM does not know the type LDVH.", e);
		}
		finally{
			ois.close();
			fis.close();
		}
	}

	/**
	 * Fonction qui demande à l'utilisateur le chemin du fichier .ldvh pour le charge 
	 * par la suite.
	 * @throws IOException
	 */
	public void chargerUnLivre() throws IOException 
	{
		boolean valide = true; // autorise ou non le chargement.
		if(instance != null){
			// On veut charger un livre, mais il y a déja un livre de chargé. 
			int selectedOption = JOptionPane.showConfirmDialog(null, 
					"Vous avez déjà un livre en cours, Voulez-vous l'écraser ?", "Confirme", JOptionPane.YES_NO_OPTION);
			if (selectedOption == JOptionPane.NO_OPTION){
				// on ne veut pas écraser le livre en cours
				valide = false;
			}
		}
		if(valide){
			JFileChooser chooser = new JFileChooser(new File("./"));
			FileNameExtensionFilter filter = new FileNameExtensionFilter(
					"Book files", "ldvh");
			chooser.setFileFilter(filter);
			chooser.setDialogTitle("Entrez un nom de fichier .ldvh (avec l'extension");
			int returnVal = chooser.showOpenDialog(null); // pop-up
			String fileName;
			if (returnVal == JFileChooser.APPROVE_OPTION) {
				fileName = chooser.getSelectedFile().getName();
				instance= charger(fileName);
				//...
				// ici un update sur les interfaces graphiques 
				//..
			} 
		}
	}

}

