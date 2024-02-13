import java.io.PipedOutputStream;
import java.io.PipedInputStream;
public class App {
    public static void main(String[] args) throws Exception {
        
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);

        Macchine m = new Macchine(pos);
        Qality q = new Qality(pis);
    
        m.start();
        q.start();

        Thread.sleep(15000);


        m.ferma();
        q.ferma();

        m.join();
        q.join();
    
    }
}
