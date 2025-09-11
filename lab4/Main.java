import java.util.Scanner;

class Competidores{
    public int inicio;
    public int end;
} 
public class Main{
    static Scanner scanner = new Scanner(System.in);

    public static int bubbleSort(Competidores[] competidores, int n){
        int trocas = 0;
        boolean trocado = true;

        int i = 0;

        while(i<n-1 && trocado){
            trocado = false;
            for(int j = 0;j<n-i-1;j++){
                if(competidores[j].end > competidores[j+1].end){
                    Competidores temp = competidores[j];
                    competidores[j]=competidores[j+1];
                    competidores[j+1]=temp;
                    trocado = true;
                    trocas++;
                }
            }
            i++;
        }

        return trocas;
    }

    public static int verificaUltrapassagem(Competidores[] competidores, int n){
        int resultado = bubbleSort(competidores, n);
        return resultado;
    }

    public static void main(String [] args){
        while(scanner.hasNext()){
            int n = scanner.nextInt();
            Competidores []competidores = new Competidores [n];

            for(int j = 0; j<n; j++){
                competidores[j] = new Competidores();  // inicializa o objeto
                competidores[j].inicio = scanner.nextInt();
            }

            for(int j = 0; j<n;j++){
                competidores[j].end = scanner.nextInt();
            }
            int resultado = verificaUltrapassagem(competidores, n);
            System.out.println(resultado);
        }
    scanner.close();
    } 
}
