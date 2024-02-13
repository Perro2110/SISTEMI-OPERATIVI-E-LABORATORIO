import java.io.Serializable;

public class Misure implements Serializable {
    float temperature;
    int umidita;

    public float getTemperature() {
        return temperature;
    }

    public int getUmidita() {
        return umidita;
    }

    public Misure(float temperature, int umidita) {
        this.temperature = temperature;
        this.umidita = umidita;
    }

    @Override
    public String toString() {
        return ""+temperature+" "+umidita+" ";
    }
}
