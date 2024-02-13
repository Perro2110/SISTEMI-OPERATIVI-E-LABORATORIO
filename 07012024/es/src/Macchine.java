import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class Macchine extends Thread{
    private PipedOutputStream pos;
    AtomicBoolean isRunnig=new AtomicBoolean();
    int Nval=0;
    float val=0;

    public Macchine(PipedOutputStream pos) {
        this.pos = pos;
        isRunnig.set(false);
    }

    @Override
    public void run() {
        isRunnig.set(true);
        Random rd=new Random();
        try (ObjectOutputStream oos = new ObjectOutputStream(pos)) {
            while(isRunnig.get()){
                try {
                    Thread.sleep(750);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                Nval ++;
                val=rd.nextFloat()*(1000 + 1000) -1000;

                Message oggetto_messaggio = new Message(Nval,val);
                oos.writeObject(oggetto_messaggio);
                oos.flush();
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    void ferma(){
        isRunnig.set(false);
    }

}
