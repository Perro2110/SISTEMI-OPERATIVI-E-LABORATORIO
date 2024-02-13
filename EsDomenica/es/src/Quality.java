import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class Quality extends Thread {
    int numCreati;
    float prec;
    float valore;
    AtomicBoolean isRunning = new AtomicBoolean();
    private PipedInputStream pis;

    public Quality(PipedInputStream pis) {
        this.isRunning.set(false);
        this.pis = pis;
    }

    @Override
    public void run() {
        isRunning.set(true);
        prec=0;
        try (ObjectInputStream ois = new ObjectInputStream(pis)) {
            while (isRunning.get()) {
                Message object_read = (Message) ois.readObject();
                if(object_read.getValore()<0){
                    System.out.println("ERRORE: "+object_read);
                }else{
                    System.out.println("Ok: "+object_read);
                }
                if(prec+((prec*20)/100) < object_read.getValore()){
                    System.out.println("Warning!!");
                }
            }
        } catch (ClassNotFoundException | IOException e) {
            e.printStackTrace();
        }

    }

    public void termina() {
        isRunning.set(false);

    }
}
