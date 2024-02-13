import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class App {
    public static void main(String[] args) throws Exception {
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);
        SimulaVento sv=new SimulaVento(pos);
        MonitoraVento mv = new MonitoraVento(pis);
        sv.start();
        mv.start();
        Thread.sleep(45000);
        sv.termina();
        mv.fermati();
    }
}
