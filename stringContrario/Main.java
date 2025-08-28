import java.util.Scanner;


public class Main {

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

	public static String inverter(String str){
		int n = str.length() - 1; //salva o tamanho da string
		String resultado = "";

		for(int i = n; i>=0; i--){
			char c = str.charAt(i); //salva caractere

			resultado += c;//adiciona caractere
		}
		return resultado;

	}

	public static void main(String[] args) {
	        Scanner scanner = new Scanner(System.in);

		String flag = "FIM"; //string de termino
		boolean continuar = true; //flag booleana


	        while (continuar) { //loop para continuar até encontrar o FIM
	            String linha = scanner.nextLine();

	            if (compare(linha, flag)) { //verifica ocorrencia do FIM e decide se o programa acaba
            		continuar = false;
        	    }else{
                	String resposta = inverter(linha);//inverte a string e salva a string invertida na variavel

	   		System.out.println(resposta);//printa resposta
	            }

	         }
        scanner.close();
	}
}
