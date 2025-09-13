import java.util.Scanner;

public class recursivo {
    static Scanner scanner = new Scanner(System.in);

    public static boolean compare(String str1, String str2) { //função que compara duas strings
		boolean resposta = true;

		if (str1.length() != str2.length()) { //verifica o tamnho, dependendo ja da falso
            		resposta = false;
        	}else{
			boolean diferente = false;
			int i = 0;
        		while (i < str1.length() && !diferente) { //while que passa por todos os caracteres
            			if (str1.charAt(i) != str2.charAt(i)) { //verifica se letra por letra é igual
                			diferente = true;
					resposta = false;
            			}
			i++;
        		}
		}
        	return resposta;
    }
    public static int stringInteiro(String str){
        int resultado = 0;
        int sinal = 1;
        int i = 0;
        int n = str.length();

        // Verifica sinal negativo
        if (str.charAt(i) == '-') {
            sinal = -1;
            i++;
        }

        
        // Converte cada caractere
        while (i<n) {
            resultado = resultado * 10 + (str.charAt(i) - '0');
            i++;
        }

        return resultado * sinal;
    }

    public static int somaDigitos(int numero){
        if(numero<=0){
            return 0;
        }else{
            return numero % 10 + somaDigitos(numero/10);
        }
    }

    public static void main(String[] args){
        String flag = "FIM";
        boolean continuar = true;

        while(continuar){
            String str = scanner.nextLine();
            if(compare(str,flag)){
                continuar = false;
            }else{
                int resultado = somaDigitos(stringInteiro(str));
                System.out.println(resultado);
            }
        }

    scanner.close();
    }
}
