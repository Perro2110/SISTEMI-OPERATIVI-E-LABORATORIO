import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class App {
    public static void main(String[] args) throws Exception {
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);
        Macchine m=new Macchine(pos);
        Quality q= new Quality(pis);
        m.start();
        q.start();
        Thread.sleep(15000);
        m.ferma();
        q.fermati();
        m.join();
        q.join();
    }
}
