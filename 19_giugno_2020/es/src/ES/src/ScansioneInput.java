package ES.src;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PipedInputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class ScansioneInput implements Runnable {
    private Thread t = null;
    PipedInputStream pis;
    AtomicBoolean isRunning = new AtomicBoolean();

    public ScansioneInput(PipedInputStream pis) {
        this.pis = pis;
        isRunning.set(false);
    }

    public void start() {
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run() {
        String line = null;
        isRunning.set(true);
        BufferedReader br = new BufferedReader(new InputStreamReader(pis));
        while (isRunning.get()) {
            try {
                line = br.readLine();
                    if (line.equals("abcde") == true) {
                        System.out.println("pericolo abcde rillevato");
                    } else if (line.equals("1234") == true) {
                        System.out.println("pericolo 1234 rillevato");
                    } else
                        System.out.println("ok");
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

    }

    public void jjoin() {
        isRunning.set(false);
    }

    public void vjoin() {
        try {
            t.interrupt();
            t.join();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
