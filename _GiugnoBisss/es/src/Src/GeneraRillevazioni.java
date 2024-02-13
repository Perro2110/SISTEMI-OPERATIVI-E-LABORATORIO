package Src;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class GeneraRillevazioni extends Thread {
    private PipedOutputStream pos;
    AtomicBoolean isRunning = new AtomicBoolean();

    public GeneraRillevazioni(PipedOutputStream pos) {
        this.pos = pos;
        this.isRunning.set(false);
        ;
    }

    @Override
    public void run() {
        try (ObjectOutputStream oos = new ObjectOutputStream(pos)) {
            isRunning.set(true);
            Random rd = new Random();
            int val = 0;
            int timestamp;
            while (isRunning.get()) {
                try {
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }

                val = rd.nextInt(200);
                timestamp = (int) System.currentTimeMillis();

                Rillevazione oggetto_messaggio = new Rillevazione(val, timestamp);
                oos.writeObject(oggetto_messaggio);
                oos.flush();

            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public void terminaRillevazioni() {
        isRunning.set(false);
        Thread.interrupted();
    }
}
