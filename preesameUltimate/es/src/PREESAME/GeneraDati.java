package PREESAME;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class GeneraDati implements Runnable {
    PipedOutputStream pos;
    AtomicBoolean isRunning = new AtomicBoolean();
    private Thread t = null;
    int valore_int;
    float valore_float;
    Random rd = new Random();

    public GeneraDati(PipedOutputStream pos) {
        this.pos = pos;
        this.isRunning.set(false);
        ;
    }

    public void start() {
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run() {
        isRunning.set(true);
        try (ObjectOutputStream oos = new ObjectOutputStream(pos)) {
            while (isRunning.get()) {
                try {
                    Thread.sleep(2500);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                valore_int = rd.nextInt(70)+15;
                valore_float = rd.nextFloat() * (25 + 5) - 5;
                Misure oggetto_messaggio = new Misure(valore_float, valore_int);
                oos.writeObject(oggetto_messaggio);
                oos.flush();
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public void finisci() throws InterruptedException {
        isRunning.set(false);
        t.join();
    }
}
