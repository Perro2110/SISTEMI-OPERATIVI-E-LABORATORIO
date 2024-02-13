import java.io.ObjectInputStream;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class App {
    public static void main(String[] args) throws Exception {

        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);
        int umidita_vecchia=0;
        float percentualediff = 0;

        GeneraDati gd = new GeneraDati(pos);
        gd.start();
        int i=0;
        ObjectInputStream ois = new ObjectInputStream(pis);

        while (percentualediff < 0.2) {
            
            Misure object_read = (Misure) ois.readObject();
            if (object_read == null)
                break; // interrompi il ciclo se non ho letto niente
            System.out.println("ToOutput: " + object_read);
            if(i==0) 
                umidita_vecchia=object_read.getUmidita();
            
            float som= Math.abs(umidita_vecchia-object_read.getUmidita());
            percentualediff= som / umidita_vecchia;
            System.out.println(percentualediff);
            umidita_vecchia=object_read.getUmidita();
            i++;
        }

        gd.finisci();

    }
}
