import java.util.Scanner;
import java.util.Random;

public class Aleatorio{
	static Scanner sc = new Scanner(System.in);

   	public static boolean compare(String str1, String str2) { //função que compara
                boolean resposta = true;

                if (str1.length() != str2.length()) { //verifica o tamnho,  dependendo da false para iguais
                        resposta = false;
                }else{
                        boolean diferente = false;
                        int i = 0;
                        while (i < str1.length() && !diferente) { //loop para verificar todos os caracteres
                                if (str1.charAt(i) != str2.charAt(i)) { //verificação em si
                                        diferente = true;
                                        resposta = false;
                                }
                        i++;
                        }
            }
                return resposta;
   	}

	public static String cifrar(String str, char letra1, char letra2){
	        int n = str.length(); //salva o tamanho da string
		String resultado = "";

        	for(int i = 0; i < n; i++) { //loop para passar por todos os caracteres
            	    char c = str.charAt(i); //salva caractere por caractere

	            if (c == letra1) { //verifica se é a letra randomizada e faz a troca de for necessario
        	        resultado += letra2;
            	    } else { //senão mantem a letra
                	resultado += c;
           	    }
        	}
           return resultado;
   	}


	public static void main(String[] args){

	        String flag = "FIM"; //string de termino
        	boolean continuar = true; //flag booleana

		Random gerador = new Random();
        	gerador.setSeed(4);


	        while(continuar){ //loop para continuar até encontrar o FIM

        	   String str = sc.nextLine();

         	   if(compare(str, flag)) { //verifica ocorrencia do FIM e decide se o >
               	        continuar = false;
           	    }else{ //printa respostas

			// Sorteia duas letras minúsculas aleatórias

                	char letra1 = (char)('a' + (Math.abs(gerador.nextInt()) % 26));
                	char letra2 = (char)('a' + (Math.abs(gerador.nextInt()) % 26));
                	String resposta = cifrar(str, letra1, letra2);

                System.out.println(resposta);
           }

        }
 	sc.close();
   }
}
