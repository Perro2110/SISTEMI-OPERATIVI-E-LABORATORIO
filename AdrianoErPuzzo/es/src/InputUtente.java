import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PipedOutputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class InputUtente implements Runnable {
    private Thread t = null;
    AtomicBoolean isRunning = new AtomicBoolean();
    private PipedOutputStream pos;

    public InputUtente(PipedOutputStream pos) {
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
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        try (BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos))) {
            String line = null;
            while (isRunning.get()) {
                line = br.readLine();
                bw.write(line);
                bw.newLine();
                bw.flush();
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public void termina() {
        isRunning.set(false);
    /*  Thread.currentThread().interrupt();
        try {
            t.join();
        } catch (InterruptedException e) {
        }
    */
    }
    public void JHOIN() throws InterruptedException{
        t.join();
    }
}
