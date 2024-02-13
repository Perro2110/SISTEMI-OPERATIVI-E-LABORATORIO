import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class Macchine extends Thread {
    int numProdCreati;
    Random rd;
    float generato;
    PipedOutputStream pos;
    AtomicBoolean isrunning = new AtomicBoolean();

    public Macchine(PipedOutputStream pos) {
        this.pos = pos;
        this.generato = 0;
        this.numProdCreati = 0;
        this.isrunning.set(false);
    }

    @Override
    public void run()  {
        
        isrunning.set(true);
        ObjectOutputStream oos;
        try {
            oos = new ObjectOutputStream(pos);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            return;
        }
        while (isrunning.get()) {
            try {
                Thread.sleep(750);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            numProdCreati++;
            Random rd = new Random();
            generato = rd.nextFloat() * (1000 - (-1000)) + (-1000);

            try {

                Message oggetto_messaggio = new Message(numProdCreati, generato);
                oos.writeObject(oggetto_messaggio);
                oos.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }

        }
        try {
            pos.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    public void ferma(){
        isrunning.set(false);
    }
}
