package Esame1;

import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class SimulaConsumi implements Runnable {
    private Thread t = null;
    Consumi c;
    AtomicBoolean isRunning = new AtomicBoolean();
    Random rd = new Random();
    float val = 0;

    public SimulaConsumi(Consumi c) {
        this.c = c;
        this.isRunning.set(false);;
    }

    public void start() {
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run() {
        isRunning.set(true);
        while(isRunning.get()){
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            val = rd.nextFloat()*(30-0)+0;
            c.setConsumi(val);
        }

    }

    public void terminaSimulazioneConsumi() throws InterruptedException {
        isRunning.set(false);
        t.join();
    }

}
