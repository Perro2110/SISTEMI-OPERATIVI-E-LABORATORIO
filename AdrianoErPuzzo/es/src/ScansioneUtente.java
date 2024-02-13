import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PipedInputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class ScansioneUtente implements Runnable {
    private Thread t = null;
    AtomicBoolean isRunning = new AtomicBoolean();
    private PipedInputStream pis;

    public void start() {
        t = new Thread(this);
        t.start();
    }

    public ScansioneUtente(PipedInputStream pis) {
        this.isRunning.set(false);
        this.pis = pis;
    }

    @Override
    public void run() {
        String line = null;
        BufferedReader br = new BufferedReader(new InputStreamReader(pis));
        isRunning.set(true);
        while(isRunning.get()){
            try {
                line = br.readLine();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            if(line.equals("abcd"))
                System.out.println("Warning abcd : " + line);
            else if(line.equals("1234"))
                System.out.println("Warning 1234 : " + line);
            else
                System.out.println("Ok : "+ line);
        }
    }

    public void termina() {
        isRunning.set(false);
    /*  Thread.currentThread().interrupt();
        try {
            t.join();
        } catch (InterruptedException e) {
        }
    */
    }
    public void JHOIN() throws InterruptedException{
        t.join();
    }
}
