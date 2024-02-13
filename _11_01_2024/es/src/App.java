public class App {
    public static void main(String[] args) throws Exception {
        Consumi c = new Consumi(0);
        SimulaConsumi sc= new SimulaConsumi(c);
        boolean flag=true;
        float newC = 0;
        float oldC = 0;
        int cont = 0;
        sc.start();
        while(flag){
            Thread.sleep(900);
            oldC=newC;
            newC = c.getNum();
            if(newC >= 20){
                cont++;
            }
            else 
                cont=0;
            if(cont == 3){
                flag=false;
            }else{
                if(newC > oldC*1.3)
                    System.out.println("Warning !!");
            }
            System.out.println("vecchio: "+oldC+" nuovo: "+newC);
        } 
        sc.fermat();
    }
}
