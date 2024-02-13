package Src;

import java.io.ObjectInputStream;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        PipedOutputStream pos = new PipedOutputStream();
        PipedInputStream pis = new PipedInputStream(pos);
        GeneraRillevazioni gr = new GeneraRillevazioni(pos);
        int soglia;
        do{
        System.out.println("Inserire val di soglia");
        Scanner sc = new Scanner(System.in);
        soglia = sc.nextInt();
        }while(soglia >200 || soglia <100);

        gr.start();
        int i = 0;
        int cw=0; 

        ObjectInputStream ois = new ObjectInputStream(pis);
        while (i < 10) {

            Rillevazione object_read = (Rillevazione) ois.readObject();
            if(object_read.getValore()<50)
                System.out.println("Basso: " + object_read);
            else if(object_read.getValore()<100)
                System.out.println("Moderato: " + object_read);
            else
                System.out.println("Alto: "+object_read);
            
            if(object_read.getValore()>soglia){
                cw++;
            }
            else{
                cw--;
            }

            if(cw == 3)
                System.out.println("Warning");
            i++;
        }
        gr.terminaRillevazioni();
        gr.join();
    }
}
