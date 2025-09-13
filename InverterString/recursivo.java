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

    public static String inverterAux(String str, int i){
        if(i>=str.length()){
            return "";
        }else{
            return inverterAux(str, i+1) + str.charAt(i);
        }
    }

    public static String inverterRecursivo(String str){
        return inverterAux(str,0);
    }

    public static void main(String[] args){
        String flag = "FIM";
        boolean continuar = true;

        while(continuar){
            String str = scanner.nextLine();
            if(compare(str,flag)){
                continuar = false;
            }else{
                String resultado = inverterRecursivo(str);
                System.out.println(resultado);
            }
        }

    scanner.close();
    }
}
