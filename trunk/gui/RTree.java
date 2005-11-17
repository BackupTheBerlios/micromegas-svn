import java.io.*;
import java.util.*;
import org.jdom.*;
import org.jdom.input.*;
import org.jdom.filter.*;
//import java.awt.*;
//import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.event.*;

public class RTree {
  String filename;
  MutableTreeNode root;
  org.jdom.Document document;
  Element racine;
  String left;
  String right;
  DefaultMutableTreeNode toNode;
  
  
  RTree(String file) {
    filename = file;
    root = new DefaultMutableTreeNode("Règles");
    SAXBuilder sxb = new SAXBuilder();
    try { document = sxb.build(new File(filename)); }
    catch(Exception e) { System.out.println(e); }
    racine = document.getRootElement();
    left = right = "";
    toNode = null;
  }

  DefaultTreeModel getModel() {
    generateModel(racine,root);
    return new DefaultTreeModel(root);
  }

  void generateModel(Element deb,MutableTreeNode mtn) {
    List listRule = deb.getChildren("Rule");
    Iterator it = listRule.iterator();
    int i = 0;
    while(it.hasNext()) {
      Element curRule = (Element)it.next();
      Rule rul = new Rule(getLeftSide(curRule),
                          getRightSide(curRule),
                          getPrincipalRule(curRule),
                          getSupport(curRule),
                          getConfidence(curRule),
                          getSpecializable(curRule),
                          getProcessed(curRule),
                          getNumber(curRule));
    DefaultMutableTreeNode dmtn = new DefaultMutableTreeNode(rul,true);
    if (rul.getSpecializable().equals("yes") &&
        rul.getLeft().equals(left) &&
        rul.getRight().equals(right)) {
      toNode = dmtn;
      }
    generateModel(curRule,dmtn);
    mtn.insert(dmtn,i++);
    }
  }

  void setNode(String l, String r) {
    left = l;
    right = r;
  }

  DefaultMutableTreeNode getNode() {
    return toNode;
  }

  private String getLeftSide(Element curRule) {
    String out = "";
    Iterator j = curRule.getChild("LeftSide").getChildren("Item").iterator();
    while(j.hasNext()) {
      Element curItem = (Element)j.next();
      if (out.length() == 0)
        out += curItem.getText();
      else out += "," + curItem.getText();
    }
    return out;
  }

  private String getRightSide(Element curRule) {
    String out = "";
    Iterator j = curRule.getChild("RightSide").getChildren("Item").iterator();
    while(j.hasNext()) {
      Element curItem = (Element)j.next();
      if (out.length() == 0)
        out += curItem.getText();
      else out += "," + curItem.getText();
    }
    return out;
  }

  private String getPrincipalRule(Element curRule) {
    return curRule.getChild("PrincipalItem").getText();
  }
  
  private String getSupport(Element curRule) {
    return curRule.getAttributeValue("support");
  }

  private String getConfidence(Element curRule) {
    return curRule.getAttributeValue("confidence");
  }

  private String getSpecializable(Element curRule) {
    return curRule.getAttributeValue("specializable");
  }

  private String getProcessed(Element curRule) {
    return curRule.getAttributeValue("processed");
  }

  private String getNumber(Element curRule) {
    return curRule.getAttributeValue("number");
  }
}