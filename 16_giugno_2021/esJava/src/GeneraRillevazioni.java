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
    }

    @Override
    public void run() {

        this.isRunning.set(true);


        Random rd = new Random();
        int num,tempo;


        try (ObjectOutputStream oos = new ObjectOutputStream(pos)) {
            while(isRunning.get()){

        try {
            
            Thread.sleep(3000);

        } catch (InterruptedException e) {
        }


                tempo=(int) System.currentTimeMillis();
                num=(int) (Math.random()*200);
                Rillevazione riv = new Rillevazione(num, tempo);
                try {
                    oos.writeObject(riv);
                    oos.flush();
                } catch (IOException e) {
                }
            }
        } catch (IOException e) {
        }
    }

    void terminaRillevazione(){
        this.isRunning.set(false);
        try {
            pos.close();
        } catch (IOException e) {

        }
    }
}
