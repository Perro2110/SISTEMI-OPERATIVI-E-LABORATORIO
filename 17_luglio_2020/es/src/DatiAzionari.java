public class DatiAzionari {
    String Indice;
    int Valore;

    public synchronized String getIndice() {
        return Indice;
    }
    public synchronized int getValore() {
        return Valore;
    }
    public synchronized void setIndice(String indice) {
        Indice = indice;
    }
    public synchronized void setValore(int valore) {
        Valore = valore;
    }

    public DatiAzionari(String indice, int valore) {
        Indice = indice;
        Valore = valore;
    }

}
