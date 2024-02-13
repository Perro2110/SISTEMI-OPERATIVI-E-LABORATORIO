import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class RecuperaDati extends Thread {
    AtomicBoolean isRunning = new AtomicBoolean();
    DatiAzionari da;
    String IndicePrecedente = null;
    Random rand = new Random();
    int numero = 0;

    public void setDa(DatiAzionari daNuovo) { // voglio che si possa modificare se e possibile che esiste il warning
        this.IndicePrecedente = this.da.getIndice();
        this.da = daNuovo;
    }

    public RecuperaDati(DatiAzionari da) {
        this.IndicePrecedente = da.getIndice();
        this.isRunning.set(false);
        this.da = da;
    }

    @Override
    public void run() {
        this.isRunning.set(true);
        while (isRunning.get()) {
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
            }

            if (IndicePrecedente.equals(da.getIndice()) != true) {
                System.out.println("Warning !!");
            }
            numero = rand.nextInt(60) + 20;
            da.setValore(numero);
            System.out.println("Indice: "+da.getIndice()+" Val: "+da.getValore());
        }
    }

    public void terminaThread() {
        isRunning.set(false);
        this.interrupt();
    }
}
