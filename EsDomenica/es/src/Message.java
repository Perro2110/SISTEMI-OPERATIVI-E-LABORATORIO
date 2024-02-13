import java.io.Serializable;

public class Message implements Serializable {
    int numCreati;
    float valore;
    public int getNumCreati() {
        return numCreati;
    }
    public float getValore() {
        return valore;
    }
    public Message(int numCreati, float valore) {
        this.numCreati = numCreati;
        this.valore = valore;
    }
    @Override
    public String toString() {
        return "valore: "+valore+" NumeroProduzione: "+numCreati;
    }
}
