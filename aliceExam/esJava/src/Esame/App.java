package Esame;

import java.io.ObjectInputStream;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class App {
    public static void main(String[] args) throws Exception {
        PipedOutputStream pos = new PipedOutputStream();
        try (PipedInputStream pis = new PipedInputStream(pos)) {
            int tt = 0;
            GeneraTemporali gt = new GeneraTemporali(pos);
            gt.start();
            ObjectInputStream ois = new ObjectInputStream(pis);
            
            for (int giri = 0; giri < 10; giri++) {
                Temporale temp = (Temporale) ois.readObject();
                if (temp.getValore() < 1) {
                    System.out.println("Assente " + temp);
                    if(tt != 0)
                        tt=0;
                } else if (temp.getValore() < 2) {
                    System.out.println("debole " + temp);
                    if(tt != 0)
                        tt=0;
                } else if (temp.getValore() < 4) {
                    System.out.println("leggera " + temp);
                    if(tt != 0)
                        tt=0;
                } else if (temp.getValore() < 6) {
                    System.out.println("moderata " + temp);
                    if(tt != 0)
                        tt=0;
                } else if (temp.getValore() >= 6) {
                    System.out.println("forte " + temp);
                    tt++;
                    if (tt == 3) {
                        System.out.println("WARNINGONE SUCCESSO 3 VOLTE");
                        tt = 0;
                    }
                }
            }
            gt.terminaTemporali();
            gt.join();
        }
    }
}
