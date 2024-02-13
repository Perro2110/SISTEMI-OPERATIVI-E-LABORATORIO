import java.io.IOException;
import java.io.PipedOutputStream;
import java.nio.charset.Charset;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class SimulaVento implements Runnable {
    private Thread t = null;
    AtomicBoolean isRunning = new AtomicBoolean();
    private PipedOutputStream pos;
    int valGen = 0;
    Random rd = new Random();

    public SimulaVento(PipedOutputStream pos) {
        this.isRunning.set(false);
        ;
        this.pos = pos;
    }

    public void start() {
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run() {
        isRunning.set(true);
        String line = null;

        while (isRunning.get()) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            valGen = rd.nextInt(101);
            line = Integer.toString(valGen);
            byte[] flusso_bytes = line.getBytes(Charset.forName("UTF-8"));
            try {
                pos.write(flusso_bytes, 0, flusso_bytes.length);
                pos.flush();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        }

    }

    public void termina() throws InterruptedException {
        isRunning.set(false);
        Thread.interrupted();
        t.join();
    }

}
