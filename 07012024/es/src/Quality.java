import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.PipedInputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class Quality extends Thread {
    private PipedInputStream pis;
    AtomicBoolean isRunnig = new AtomicBoolean();
    Random rd = new Random();

    // COSTRUTTORE
    public Quality(PipedInputStream pis_da_main) {
        pis = pis_da_main;
    }

    @Override
    public void run() {
        isRunnig.set(true);
        try (ObjectInputStream ois = new ObjectInputStream(pis)) {
            while(isRunnig.get()){
                Message object_read = (Message)ois.readObject();
                if(object_read.getVal() <0)
                    System.out.println("Errore negativo: "+ object_read);
                else 
                    System.out.println("Ok: " + object_read);
            }
        } catch (ClassNotFoundException | IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public void fermati() {
        isRunnig.set(false);
    }

}
