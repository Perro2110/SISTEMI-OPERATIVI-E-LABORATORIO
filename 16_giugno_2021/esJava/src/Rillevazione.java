import java.io.Serializable;

public class Rillevazione implements Serializable {
    int valore;

    public int getValore() {
        return valore;
    }

    int timestampp;

    public Rillevazione(int valore, int timestampp) {
        this.valore = valore;
        this.timestampp = timestampp;
    }
    
    @Override
    public String toString() {
        // TODO Auto-generated method stub
        return "val al" + timestampp + " uguale a: " + valore;
    }

}
