import java.util.Scanner;

public class Main{
   static Scanner sc = new Scanner(System.in);

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


   public static String cifrar(String str){
	int n = str.length(); //salva o tamanho da string
	StringBuilder resultado = new StringBuilder(); //utiliza o builder para adicionar caractere por caractere

	for(int i = 0; i < n; i++) { //loop para passar por todos os caracteres e adicionar 3 em cada um
            char c = str.charAt(i); //salva caractere por caractere para adicionar o 3

	 if (c >= 32 && c <= 126) {//verifica se é um caractere cifravel
            int posicao = c - 32;
            int novaPosicao = (posicao + 3) % 95;
            c = (char) (32 + novaPosicao);
	  }
            resultado.append(c); //adiciona o caractere na string
        }

        return resultado.toString();
   }

   public static void main(String[] args){

	String flag = "FIM"; //string de termino
        boolean continuar = true; //flag booleana


	while(continuar){ //loop para continuar até encontrar o FIM

	   String str = sc.nextLine();

	   if(compare(str, flag)) { //verifica ocorrencia do FIM e decide se o programa acaba
                        continuar = false;
           }else{ //printa respostas
           	String resposta = cifrar(str);

	   	System.out.println(resposta);
	   }

	}
	sc.close();

   }
}
