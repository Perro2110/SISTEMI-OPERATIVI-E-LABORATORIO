import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.PipedInputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class Qality extends Thread {

    PipedInputStream pis;
    AtomicBoolean isrunning = new AtomicBoolean();

    // COSTRUTTORE
    public Qality(PipedInputStream pis_da_main) {
        pis = pis_da_main;
        this.isrunning.set(false);
    }

    public void run() {
        this.isrunning.set(true);
        ObjectInputStream ois;
        try {
            ois = new ObjectInputStream(pis);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            return;
        }
        while (isrunning.get()) {
            try {
                Message object_read = (Message) ois.readObject();
                System.out.println("Stampo: " + object_read.getMess());
            } // fine try
            catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
        try {
            pis.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    } // fine metodo run()

    public void ferma() {
        isrunning.set(false);
    }
}