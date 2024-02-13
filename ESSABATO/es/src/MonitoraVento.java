import java.io.IOException;
import java.io.PipedInputStream;
import java.nio.charset.Charset;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicBoolean;

public class MonitoraVento implements Runnable {
    private Thread t = null;
    AtomicBoolean isRunning = new AtomicBoolean();
    private PipedInputStream pis;
    int valRicevuto = 0;
    Random rd = new Random();

    public MonitoraVento(PipedInputStream pis) {
        this.isRunning.set(false);
        this.pis = pis;
    }

    public void start() {
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run() {
        isRunning.set(true);
        int nread;
        byte lettura_bytes[] = new byte[1024];
        Scanner sc;
        while (isRunning.get()) {
            try {
                nread = pis.read(lettura_bytes);
            } catch (IOException e) {
                return;
            }
            byte effettivamente_letti[] = Arrays.copyOfRange(lettura_bytes, 0, nread);
            // dai byte grezzi crea stringa di senso compiuto secondo standard UTF-8
            String message = new String(effettivamente_letti, Charset.forName("UTF-8"));
            sc=new Scanner(message);
            valRicevuto=sc.nextInt();
            if(valRicevuto < 10){
                System.out.println("vento leggero: "+message);
            }else if(valRicevuto < 30){
                System.out.println("vento moderato: "+message);
            }else if(valRicevuto < 50)
            {
                System.out.println("vento forte: "+message);
            }else if(valRicevuto < 75){
                System.out.println("vento tempestoso: "+message);
            }else{
                System.out.println("vento Violenza: "+message);                
            }
        }

    }

    public void fermati() throws InterruptedException {
        isRunning.set(false);
        Thread.interrupted();
        t.join();
    }

}
