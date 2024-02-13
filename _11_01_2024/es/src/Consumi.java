public class Consumi{
    float num;

    public Consumi(float num) {
        this.num = num;
    }

    public synchronized float getNum() {
        return num;
    }

    public synchronized void setNum(float num) {
        this.num = num;
    }
}
