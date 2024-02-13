import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class Machine extends Thread {
    int numCreati;
    float valore;
    AtomicBoolean isRunning = new AtomicBoolean();
    private PipedOutputStream pos;
    Random rd = new Random();

    public Machine(PipedOutputStream pos) {
        this.isRunning.set(false);
        this.pos = pos;
    }

    @Override
    public void run() {
        isRunning.set(true);
        numCreati = 0;
        try (ObjectOutputStream oos = new ObjectOutputStream(pos)) {
            while (isRunning.get()) {
                numCreati++;
                try {
                    Thread.sleep(750);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                valore = rd.nextFloat() * (1000 + 1000) - 1000;
                Message oggetto_messaggio = new Message(numCreati, valore);
                oos.writeObject(oggetto_messaggio);
                oos.flush();
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    public void termina() {
        isRunning.set(false);
    }
}
