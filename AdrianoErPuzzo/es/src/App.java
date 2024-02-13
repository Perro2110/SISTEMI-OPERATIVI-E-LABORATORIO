import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class App {
    public static void main(String[] args) throws Exception {
        {
            PipedOutputStream pos = new PipedOutputStream();
            PipedInputStream pis = new PipedInputStream(pos);
            InputUtente     iu = new InputUtente(pos);
            ScansioneUtente su = new ScansioneUtente(pis);
            iu.start();
            su.start();
            Thread.sleep(300);
            iu.termina();
            su.termina();
            //System.exit(0);
            iu.JHOIN();
            su.JHOIN();
        }
    }
}
