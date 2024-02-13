import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class RillevatoreAria extends Thread {
    PipedOutputStream pos = new PipedOutputStream();
    AtomicBoolean isRunning = new AtomicBoolean();

    public RillevatoreAria(PipedOutputStream pos) {
        isRunning.set(false);
        this.pos = pos;
    }

    @Override
    public void run() {
        isRunning.set(true);
        int num;
        long temp = 0;
        long tempPrec = 0;
        String line;
        Random rnd = new Random();

        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));

        while (isRunning.get()) {
            tempPrec=temp;
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            num = rnd.nextInt(110);
            // tempPrec=temp;
            temp = System.currentTimeMillis();

            if (num < 20)
                line = "Basso: " + Integer.toString(num) + " " + Long.toString(temp);
            else if (num < 75)
                line = "MEDIO: " + Integer.toString(num) + " " + Long.toString(temp);
            else
                line = "Alto: " + Integer.toString(num) + " " + Long.toString(temp);

            if (Math.abs(temp - tempPrec) >= 15000)
                line = line + " Attenzione";

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

    public void fermatiRillevatoreDaria() {
        isRunning.set(false);
    }
}
