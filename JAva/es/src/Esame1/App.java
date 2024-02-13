package Esame1;

public class App {
    public static void main(String[] args) throws Exception {
        Consumi cons = new Consumi(0);
        SimulaConsumi sc = new SimulaConsumi(cons);
        sc.start();
        int flag = 0;
        float valP = 0;
        float valAtt = 0;
        while (flag != 3) {
            Thread.sleep(900);
            valP = valAtt;
            valAtt = cons.getConsumi();
            if (valP + (valP * 30) / 100 < valAtt) {
                System.out.println("Warning "+valAtt);
            }else{
                System.out.println("valore: "+valAtt);
            }
            if(valAtt > 20){
                flag++;
            }else{
                flag=0;
            }
        }
        sc.terminaSimulazioneConsumi();
    }
}
