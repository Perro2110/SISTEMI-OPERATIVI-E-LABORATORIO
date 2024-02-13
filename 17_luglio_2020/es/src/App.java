import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        DatiAzionari da;
        System.out.println("Inserire nome indice");
        Scanner sc = new Scanner(System.in);
        String indice=sc.nextLine();
        da=new DatiAzionari(null, 0);
        da.setIndice(indice);
        RecuperaDati rd=new RecuperaDati(da);
        rd.start();
        Thread.sleep(7000);
        while(da.getValore()<70 && da.getValore()>30){
            Thread.sleep(7000);
        }
        rd.terminaThread();
        System.out.println("Terminato generando: "+da.getValore());
        rd.join();
       
    
    }
}
