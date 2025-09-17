import java.util.Scanner;

class Cartas{
    String lingua;
    String mensagem;
}

public class Main{
    static Scanner scanner = new Scanner(System.in);
    public static void main(String[]args){

        int n = scanner.nextInt();
        scanner.nextLine(); // Consome a quebra de linha após o número

        Cartas [] carta = new Cartas [n];

        for(int i = 0; i<n ; i++){
            carta[i] = new Cartas();

            carta[i].lingua = scanner.nextLine();
            carta[i].mensagem = scanner.nextLine();
        }

        int num = scanner.nextInt();
        scanner.nextLine(); // Consome a quebra de linha após o número

        String [] nome = new String [num];
        String [] lingua = new String [num];

        for(int i = 0; i<num ; i++){

            nome[i] = scanner.nextLine();
            lingua[i] = scanner.nextLine();
        }

        for(int i = 0; i<num ; i++){
            for(int j = 0; j<n;j++){
                if(carta[j].lingua.equals(lingua[i])){
                    System.out.println(nome[i]);
                    System.out.println(carta[j].mensagem);
                    System.out.println(); // Linha em branco após cada etiqueta
                }
            }
        }
        scanner.close();
    }
}