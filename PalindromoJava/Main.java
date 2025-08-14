import java.util.Scanner;


public class Main {
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

	        while (true) {
	            String linha = scanner.nextLine();

	            if (linha.equals("FIM")) {
	                break;
	            }

	            if (ehPalindromo(linha)) {
	                System.out.println("SIM");
	            } else {
	                System.out.println("NAO");
	            }
	        }
        scanner.close();
    }
}
