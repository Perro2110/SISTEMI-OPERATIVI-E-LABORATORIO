package PREESAME;

import java.io.ObjectInputStream;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class App {
    public static void main(String[] args) throws Exception {
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);
        GeneraDati gd = new GeneraDati(pos);
        gd.start();
        boolean flag = true;
        float umiPr = 0;  // per gestire percentuali tengo in considerazione la ,
        float umiAt = 0;  // poi parserò
        int i = 0;
        ObjectInputStream ois = new ObjectInputStream(pis);
        while (flag) {
            Misure object_read = (Misure) ois.readObject();
            System.out.println("ToOutput: " + object_read);
            umiPr = umiAt;
            umiAt = (float) object_read.getUmidita();
            if (i != 0)
                if (umiPr + ((umiPr * 20) / 100) < umiAt || umiPr - ((umiPr * 20) / 100) > umiAt) {
                    flag = false;
                }
            i++;
        }
        gd.finisci();
    }
}
