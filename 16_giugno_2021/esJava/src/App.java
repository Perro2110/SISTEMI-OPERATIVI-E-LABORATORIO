import java.io.ObjectInputStream;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Inserire valore di soglia critico");
        Scanner sc = new Scanner(System.in);
        int valoreSoglia = sc.nextInt();
        // System.out.println(valoreSoglia);
        sc.close();
        
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);

        GeneraRillevazioni gr = new GeneraRillevazioni(pos);

        gr.start();
        int volte = 0;

        ObjectInputStream ois = new ObjectInputStream(pis);
        for (int i = 0; i < 10; i++) {
            Rillevazione object_read = (Rillevazione) ois.readObject();
            if (object_read.getValore() <= 50)
                System.out.println("Basso: "+object_read);
            else if (object_read.getValore() < 100)
                System.out.println("Moderato: "+object_read);
            else if (object_read.getValore() >= 100)
                System.out.println("Alto: "+object_read);

            if (valoreSoglia < object_read.getValore())
                volte++;

            if (volte == 3) {
                System.out.println("ATTENZIONE SUPERATE PER TRE VOLTE!!");
                volte=999;
            }
        }
        pos.close();
        pis.close();
        ois.close();
        
        gr.terminaRillevazione();
        gr.join();

    }
}
