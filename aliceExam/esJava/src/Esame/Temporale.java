package Esame;

import java.io.Serializable;

public class Temporale implements Serializable {
    float valore;
    String giorno;

    public float getValore() {
        return valore;
    }

    public String getGiorno() {
        return giorno;
    }

    public Temporale(float valore, String giorno) {
        this.valore = valore;
        this.giorno = giorno;
    }

    @Override
    public String toString() {
        // TODO Auto-generated method stub
        return " giorno "+giorno+" valore "+valore;
    }
}
