import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class GeneraDati implements Runnable {

    private Thread t = null;
    PipedOutputStream pos = new PipedOutputStream();
    AtomicBoolean isRunnig = new AtomicBoolean();
    Random rd = new Random();

    public GeneraDati(PipedOutputStream pos) {
        this.pos = pos;
        isRunnig.set(false);
    }

    public void start() {
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run() {
        try (ObjectOutputStream oos = new ObjectOutputStream(pos)) {
            isRunnig.set(true);
            while (isRunnig.get()) {
                try {
                    Thread.sleep(2500);
                } catch (InterruptedException e) {
                }
                float temp = rd.nextFloat() * (25 + 5) - 5;
                int umidita = rd.nextInt(71)+15;
                Misure ms = new Misure(temp, umidita);
                oos.writeObject(ms);
                oos.flush();
            }
        } catch (IOException e) {
        }

    }

    public void finisci() {
        isRunnig.set(false);
        t.stop();
        try {
            t.join();
        } catch (InterruptedException e) {
        }
    }

}
