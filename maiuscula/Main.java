import java.util.Scanner;

public class Main {
        public static int numeroMaiusculas(String str) {

                int contador = 0;

                for(int i=0;i<str.length();i++){
		   if(str.charAt(i)>='A' && str.charAt(i)<='Z'){
			contador++;
		   }
		}
        return contador;
        }

        public static void main(String[] args) {
                Scanner scanner = new Scanner(System.in);

        while (true) {
                    String linha = scanner.nextLine();

                    if (linha.equals("FIM")) {
                        break;
                    }

		    int resposta = numeroMaiusculas(linha);

                    System.out.println(resposta);
        }
        scanner.close();
    }
}
