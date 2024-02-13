package PREESAME;

import java.io.Serializable;

public class Misure implements Serializable {
    float temperatura;
    int umidita;

    public float getTemperatura() {
        return temperatura;
    }

    public int getUmidita() {
        return umidita;
    }

    public Misure(float temperatura, int umidita) {
        this.temperatura = temperatura;
        this.umidita = umidita;
    }

    public String toString() {
        return "umidita: "+umidita+" temperatura: "+temperatura;
    }
}
