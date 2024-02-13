package Esame1;


public class Consumi{
    float consumi;

    public synchronized float getConsumi() {
        return consumi;
    }

    public synchronized void setConsumi(float consumi) {
        this.consumi = consumi;
    }

    public Consumi(float consumi) {
        this.consumi = consumi;
    }


}
