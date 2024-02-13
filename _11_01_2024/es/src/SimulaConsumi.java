import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class SimulaConsumi implements Runnable {
    private Thread t = null;
    AtomicBoolean isRunning = new AtomicBoolean();
    Consumi c;
    int num;
    Random rd=new Random();
    
    public SimulaConsumi(Consumi c ) {
        this.c = c;
        this.isRunning.set(false);
    }

    public void start() {
        t = new Thread(this);
        t.start();
        }

    @Override
    public void run() {
        isRunning.set(true);
        while(isRunning.get()){
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            num=rd.nextInt(30);
            c.setNum(num);
        }
    }
    public void fermat(){
        isRunning.set(false);
    }

}
