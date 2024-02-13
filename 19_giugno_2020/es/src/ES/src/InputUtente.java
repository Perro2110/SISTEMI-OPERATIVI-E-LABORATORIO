package ES.src;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PipedOutputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class InputUtente implements Runnable {
    private Thread t = null;
    PipedOutputStream pos;
    AtomicBoolean isRunning = new AtomicBoolean();

    public InputUtente(PipedOutputStream pos) {
        this.pos = pos;
        isRunning.set(false);
    }

    public void start() {
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run() {
        isRunning.set(true);
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        while (isRunning.get()) {
            String line = null;
            try {
                line = br.readLine();
                bw.write(line);
                bw.newLine();
                bw.flush();

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
