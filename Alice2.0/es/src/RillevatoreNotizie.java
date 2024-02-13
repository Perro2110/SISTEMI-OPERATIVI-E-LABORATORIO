import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class RillevatoreNotizie extends Thread {
    AtomicBoolean isRunning = new AtomicBoolean();
    PipedOutputStream pos;
    int num;
    int numS;
    String line = null;
    Random rd = new Random();

    public RillevatoreNotizie(PipedOutputStream pos) {
        this.isRunning.set(false);
        ;
        this.pos = pos;
    }

    public void run() {
        isRunning.set(true);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        while (isRunning.get()) {
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            num = rd.nextInt(501);
            numS = rd.nextInt(3);
            if (numS == 0) {
                line = num + " cronaca";
            }
            if (numS == 1) {
                line = num + " sport";
            }
            if (numS == 2) {
                line = num + " politica";
            }
            try {
                bw.write(line);
                bw.newLine();
                bw.flush();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        }

    }

    public void fermaRillevatoreNotizie() {
        isRunning.set(false);
    }

}
