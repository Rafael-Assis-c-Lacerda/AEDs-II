import java.util.Scanner;


public class Main {

	public static boolean compareManual(String str1, String str2) {
		boolean resposta = true;

		if (str1.length() != str2.length()) {
            		resposta = false;
        	}else{
			boolean diferente = false;
			int i = 0;
        		while (i < str1.length() && !diferente) {
            			if (str1.charAt(i) != str2.charAt(i)) {
                			diferente = true;
					resposta = false;
            			}
			i++;
        		}
		}
        	return resposta;
    	}


	public static boolean ehPalindromo(String str) {

        	int i = 0;
        	int j = str.length() - 1;

	        while (i < j) {
	            if (str.charAt(i) != str.charAt(j)) {
	                return false;
           	    }
        	i++;
            	j--;
        	}
        return true;
    	}

	public static void main(String[] args) {
	        Scanner scanner = new Scanner(System.in);

		String flag = "FIM"; //string de termino
		boolean continuar = true; //flag booleana


	        while (continuar) { //loop para continuar até encontrar o FIM
	            String linha = scanner.nextLine();

	            if (compare(linha, flag)) { //verifica ocorrencia do FIM e decide se o >
            		continuar = false;
        	    }else{
                	if (ehPalindromo(linha)) { //if e else que verifica se é palind>
                        	System.out.println("SIM");
                	} else {
                        	System.out.println("NAO");
                	}
	            }
		
	         }
        scanner.close();
	}
}
