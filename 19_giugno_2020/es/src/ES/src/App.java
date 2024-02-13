package ES.src;

import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class App {
    public static void main(String[] args) throws Exception {
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);
        InputUtente iu = new InputUtente(pos);
        ScansioneInput si = new ScansioneInput(pis);
        iu.start();
        si.start();
        Thread.sleep(1000);
        
        si.jjoin();
        iu.jjoin();


        iu.vjoin();
        si.vjoin();
    }
}
