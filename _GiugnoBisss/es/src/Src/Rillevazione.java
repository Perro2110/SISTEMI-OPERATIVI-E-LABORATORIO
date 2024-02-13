package Src;
import java.io.Serializable;

public class Rillevazione implements Serializable {
    int  valore;
    int timestamp;
    public int getValore() {
        return valore;
    }
    public int getTimestamp() {
        return timestamp;
    }
    public Rillevazione(int valore, int timestamp) {
        this.valore = valore;
        this.timestamp = timestamp;
    }
    @Override
    public String toString() {
        // TODO Auto-generated method stub
        return " "+valore+" "+timestamp;
    }

}
