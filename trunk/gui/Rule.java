public class Rule {
  String left;
  String right;
  String principal;
  String sup;
  String conf;
  String spe;
  String proc;
  String number;
  
  public Rule() {
    left = right = principal = sup = conf = spe = proc = number = "";
  }

  public Rule(String l,String r,String p, String supp, String confi, String spec, String proce, String num) {
    left = l;
    right = r;
    principal = p;
    sup = supp;
    conf = confi;
    spe = spec;
    proc = proce;
    number = num;
  }

  public String affiche() {
    return left + " -> " + right + "\n"
                + "\tNumber : " + number + "\n"
                + "\tPrincipal : " + principal + "\n"
                + "\tSupport : " + sup + "\n"
                + "\tConfidence : " + conf + "\n"
                + "\tSpecializable : " + spe + "\n"
                + "\tProcessed : " + proc;
  }

  public String toString() {
    return left + " -> " + right;
  }

  public String getLeft() { return left; }
  public String getRight() { return right; }
  public String getNumber() { return number; }
  public String getPrincipal() { return principal; }
  public String getProcessed() { return proc; }
  public String getConfidence() { return conf; }
  public String getSupport() { return sup; }
  public String getSpecializable() { return spe; }
}