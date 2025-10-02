import java.util.Scanner;
import java.io.*;

class Game{
    private int id;
    private String name;
    private String Date;
    private int jogadores;
    private float preco;
    private String [] linguas;
    private int notaEspecial;
    private float notaUsuario;
    private int conquistas;
    private String [] publishers;
    private String [] developers;
    private String [] categorias;
    private String [] generos;
    private String [] tags;

    public void setID(String id){
        this.id = Integer.parseInt(id);
    }
    public void setNome(String name) {
        this.name = name;
    }
    public int getID(){
        return this.id;
    }
}

public class Main{
    static Scanner scanner = new Scanner(System.in);
    static Scanner scannerArq = new Scanner("games.csv");

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

    public static void sets(Game game, String array[]){

    }

    public static void main(String []args) throws FileNotFoundException{
        Game game[] = new Game[2000];
        int jogos = 0;

        while(scannerArq.hasNextLine()) {
            scannerArq.nextLine();

            String entrada = scannerArq.nextLine();
            String array[] = new String[14]; 
            String aux = "";
            int contador = 0;
            boolean aspas = false;

            for(int i = 0; i<entrada.length(); i++){
                char c = entrada.charAt(i);

                if(c == '"'){
                    aspas = true;
                
                }else if(c == ',' && !aspas){
                    array[contador] = aux;
                    contador++;
                    aux = "";
                }else{
                    aux = aux + c;
                }
            }
            array[contador] = aux;
            game[jogos] = new Game();
            sets(game[jogos], array);
            jogos++;
        }

        String flag = "FIM"; //string de termino
		boolean continuar = true; //flag booleana
        
	    while (continuar) { //loop para continuar até encontrar o FIM
	        String busca = scanner.nextLine();

	        if (compare(busca, flag)) { //verifica ocorrencia do FIM e decide se o programa acaba
            	continuar = false;
        	}else{
                int idBusca = Integer.parseInt(busca);
                for(int i = 0; i < jogos; i++) {
                    if(idBusca == game[i].getID()) {
                        System.out.println(game[i].toString());
                        i = jogos;
                    }
                }
	        }

	    }
        scanner.close();
        scannerArq.close();
    }
}