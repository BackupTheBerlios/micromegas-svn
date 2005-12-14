import java.io.*;
import java.util.*;
import java.lang.Runtime;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.event.*;

public class ui {
  
  static String filename;
  static DefaultTreeModel model;
  static JTextArea textPane;
  
  public static void main(String[] args) {
    if (args.length == 0) {
      filename = "";
    } else filename = args[0];
    display();
  }

  static public void display() {
    //Dessine l'interface
    final JFrame frame = new JFrame("ARF v1.0");
    
    
    if (filename.equals("")) {
      model = null;
    } else {
    //Création de l'arborescence des règles
    RTree rt = new RTree(filename);
    model = rt.getModel();
    }
    final JTree tree = new JTree(model);
    tree.setRootVisible(false);
    tree.setShowsRootHandles(true);
    tree.getSelectionModel().setSelectionMode
        (TreeSelectionModel.SINGLE_TREE_SELECTION);
    
    // Ajout d'une zone de texte
    textPane = new JTextArea();
    textPane.setEditable(false);
    textPane.setRows(7);

    //Listener qui detecte les selections dans l'arbre graphique
    tree.addTreeSelectionListener(new TreeSelectionListener() {
      public void valueChanged(TreeSelectionEvent e) {
        TreePath tp = e.getNewLeadSelectionPath();
        try {
        DefaultMutableTreeNode tn = (DefaultMutableTreeNode)tp.getLastPathComponent();
        textPane.setText(((Rule)tn.getUserObject()).affiche()); }
        catch(Exception excpt) {}
      }
    });

    // Création du menu
    JMenu fichiers = new JMenu("Fichier");
    JMenuItem ouvrir = new JMenuItem("Ouvrir");
        ouvrir.setMnemonic(KeyEvent.VK_O);
        ouvrir.setAccelerator(
          KeyStroke.getKeyStroke(KeyEvent.VK_O, Event.CTRL_MASK));
        ouvrir.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            JFileChooser chooser = new JFileChooser(new File("."));
            chooser.addChoosableFileFilter(new MonFiltre());
            int result = chooser.showOpenDialog(frame);
            if (result == JFileChooser.CANCEL_OPTION) return;
            try {
              filename = chooser.getName(chooser.getSelectedFile());
              textPane.setText("Ouverture de " + filename + "\n");
              RTree rt = new RTree(filename);
              model = rt.getModel();
              model.reload();
              tree.setModel(model);
              tree.revalidate();
              tree.repaint();
            } catch (Exception err) {
              textPane.setText("Impossible de charger le fichier: " + err + "\n");
            }
          }});
        fichiers.add(ouvrir);
    JMenuItem touv = new JMenuItem("Convertir une table");
        touv.setMnemonic(KeyEvent.VK_C);
        touv.setAccelerator(
          KeyStroke.getKeyStroke(KeyEvent.VK_C, Event.CTRL_MASK));
        touv.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            JFileChooser chooser = new JFileChooser(new File("."));
            chooser.addChoosableFileFilter(new MonFiltreTable());
            int result = chooser.showOpenDialog(frame);
            if (result == JFileChooser.CANCEL_OPTION) return;
            try {
              filename = chooser.getName(chooser.getSelectedFile());
              textPane.setText("Initialisation avec " + filename + "\n");
              Runtime run = Runtime.getRuntime();
              try {
                run.exec("./arf -a " + filename).waitFor();
              } catch (Throwable t) { t.printStackTrace(); }
              filename = filename.substring(0,filename.lastIndexOf(".table.xml")) + ".arbo.xml";
              textPane.setText("Ouverture de " + filename + "\n");
              RTree rt = new RTree(filename);
              model = rt.getModel();
              model.reload();
              tree.setModel(model);
              tree.revalidate();
              tree.repaint();
            } catch (Exception err) {
              textPane.setText("Conversion impossible: " + filename + ":" + err + "\n");
            }
          }});
        fichiers.add(touv);
    JMenuItem saveItem = new JMenuItem("Enregistrer sous...");
        saveItem.setMnemonic(KeyEvent.VK_E);
        saveItem.setAccelerator(
          KeyStroke.getKeyStroke(KeyEvent.VK_E, Event.CTRL_MASK));
        saveItem.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            JFileChooser chooser = new JFileChooser(new File("."));
            chooser.addChoosableFileFilter(new MonFiltre());
            int result = chooser.showSaveDialog(frame);
            if (result == JFileChooser.CANCEL_OPTION) return;
            try {
              String nf = chooser.getName(chooser.getSelectedFile());
              if (!nf.toLowerCase().endsWith(".arbo.xml")) nf += ".arbo.xml";
              textPane.setText("Enregistrement vers " + nf + "\n");
              Runtime run = Runtime.getRuntime();
              try {
                run.exec("cp " + filename + " " + nf).waitFor();
              } catch (Throwable t) { t.printStackTrace(); }
              filename = nf;
            } catch (Exception err) {
              textPane.setText("Impossible d'enregistrer le fichier: " + err + "\n");
            }
        }});
        fichiers.add(saveItem);
    JMenuItem quitItem = new JMenuItem("Quitter");
        quitItem.setMnemonic(KeyEvent.VK_Q);
        quitItem.setAccelerator(
          KeyStroke.getKeyStroke(KeyEvent.VK_Q, Event.CTRL_MASK));
        quitItem.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) { System.exit(0); }});
        fichiers.add(quitItem);
    
    JMenu ope = new JMenu("Opérations");
    //Ajoute un bouton "spécialiser"
    JMenuItem spec = new JMenuItem("Spécialiser");
    spec.setMnemonic(KeyEvent.VK_S);
    spec.setAccelerator(
      KeyStroke.getKeyStroke(KeyEvent.VK_S, Event.CTRL_MASK));
    spec.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        TreePath tp = tree.getSelectionPath();
        try {
          DefaultMutableTreeNode tn = (DefaultMutableTreeNode)tp.getLastPathComponent();
          Rule rl = (Rule)tn.getUserObject();
          if ((rl.getSpecializable().equals("yes"))
           ){
              //System.out.println("./arf -s " + filename + " -n " + rl.getNumber() + " -o spe.arbo.xml");
              Runtime run = Runtime.getRuntime();
              try {
              run.exec("./arf -s " + filename + " -n " + rl.getNumber() + " -o spe.arbo.xml").waitFor();
              } catch (Throwable t) { t.printStackTrace(); }
              filename = "spe.arbo.xml";
              RTree rt = new RTree(filename);
              rt.setNode(rl.getLeft(),rl.getRight());
              model = rt.getModel();
              model.reload();
              tree.setModel(model);
              tree.revalidate();
              tree.repaint();
              tree.setSelectionPath(new TreePath(rt.getNode().getPath()));
              tree.expandPath(new TreePath(rt.getNode().getPath()));
              }
          else {
            textPane.setText("This item can't be specialized\n");
          }
        } catch(Exception excpt) {}
      }
    });
    ope.add(spec);
    //Ajoute un bouton "sauter"
    JMenuItem saut = new JMenuItem("Sauter");
    saut.setMnemonic(KeyEvent.VK_J);
    saut.setAccelerator(
      KeyStroke.getKeyStroke(KeyEvent.VK_J, Event.CTRL_MASK));
    saut.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        TreePath tp = tree.getSelectionPath();
        try {
          DefaultMutableTreeNode tn = (DefaultMutableTreeNode)tp.getLastPathComponent();
          Rule rl = (Rule)tn.getUserObject();
          if ((rl.getSpecializable().equals("yes"))){
              //System.out.println("./arf -j " + filename + " -n " + rl.getNumber() + " -o spe.arbo.xml");
              Runtime run = Runtime.getRuntime();
              try {
              run.exec("./arf -j " + filename + " -n " + rl.getNumber() + " -o spe.arbo.xml").waitFor();
              } catch (Throwable t) { t.printStackTrace(); }
              filename = "spe.arbo.xml";
              RTree rt = new RTree(filename);
              rt.setNode(rl.getLeft(),rl.getRight());
              model = rt.getModel();
              model.reload();
              tree.setModel(model);
              tree.revalidate();
              tree.repaint();
              tree.setSelectionPath(new TreePath(rt.getNode().getPath()));
              tree.expandPath(new TreePath(rt.getNode().getPath()));
              }
          else {
            textPane.setText("You can't jump from this item\n");
          }
        } catch(Exception excpt) {}
      }
    });
    ope.add(saut);
  
    //Dessin de la barre de menu
    JMenuBar menuBar = new JMenuBar();
    menuBar.add(fichiers);
    menuBar.add(ope);
    frame.setJMenuBar(menuBar);
    
    frame.setSize(500,500);
    frame.getContentPane().add( new JScrollPane(tree));
    frame.getContentPane().add( new JScrollPane(textPane), BorderLayout.SOUTH);
    frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
    frame.setVisible(true);
  }
}

class MonFiltre extends javax.swing.filechooser.FileFilter {
  public boolean accept(File file) {
    String filename = file.getName();
      return filename.endsWith(".arbo.xml");
  }
  public String getDescription() {
    return "Arborescence XML";
  }
}

class MonFiltreTable extends javax.swing.filechooser.FileFilter {
  public boolean accept(File file) {
    String filename = file.getName();
      return filename.endsWith(".table.xml");
  }
  public String getDescription() {
    return "Table XML";
  }
}