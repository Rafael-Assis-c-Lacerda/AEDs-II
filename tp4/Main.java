import java.util.Scanner;
import java.io.*;

class Game{
    //atributos dos games
    private int id;
    private String name;
    private String date;
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


    //metodos sets (utilizados para popular o objeto)
    public void setId(String id){
        this.id = Integer.parseInt(id);
    }
    public void setNome(String name) {
        this.name = name;
    }
    public void setData(String data) { //metodo data que troca palavra pelo numero e trata as excessões
        String mes = "", dia = "", ano = "", resp = "";
        for(int i = 0; i < 3; i++) {
            mes += data.charAt(i);
        }
        if(data.charAt(5) == ',') {
            dia += "0";
            dia += data.charAt(4);
            for(int i = 7; i < data.length(); i++) {
                ano += data.charAt(i);
            }
        }
        else {
            dia += data.charAt(4);
            dia += data.charAt(5);
            for(int i = 8; i < data.length(); i++) {
                ano += data.charAt(i);
            }
        }
        switch(mes) {
            case "Jan": mes = "01"; break;
            case "Feb": mes = "02"; break;
            case "Mar": mes = "03"; break;
            case "Apr": mes = "04"; break;
            case "May": mes = "05"; break;
            case "Jun": mes = "06"; break;
            case "Jul": mes = "07"; break;
            case "Aug": mes = "08"; break;
            case "Sep": mes = "09"; break;
            case "Oct": mes = "10"; break;
            case "Nov": mes = "11"; break;
            case "Dec": mes = "12"; break;
            default: mes = "01"; break;     
        }
        resp = dia + "/" + mes + "/" + ano;
        this.date = resp;
    }
    public void setJogadores(String jogadores) {
        String aux = "";
        for(int i = 0; i < jogadores.length(); i++) {
            if(jogadores.charAt(i) >= '0' && jogadores.charAt(i) <= '9') {
                aux += jogadores.charAt(i);
            }
        }
        this.jogadores = Integer.parseInt(aux);
    }

    public void setPreco(String preco) {
        if(compare(preco,"Free to play")) {
            this.preco = 0.0f;
        }
        else {
            this.preco = Float.parseFloat(preco);
        } 
    }

    public void setLinguas(String linguas) {
        this.linguas = formatar(linguas,0);
    }

    public void setNotaEspecial(String notaEspecial) {
        if(notaEspecial == null) {
            this.notaEspecial = -1;
        }
        else {
            this.notaEspecial = Integer.parseInt(notaEspecial);
        }
    }

    public void setNotaUsuario(String notaUsuario) {
        if(notaUsuario == null || notaUsuario == "tbd") {
            this.notaUsuario = -1.0f;
        }
        else {
            this.notaUsuario = Float.parseFloat(notaUsuario);
        }
    }

    public void setConquistas(String conquistas) {
        if(conquistas == null) {
            this.conquistas = 0;
        }
        else {
            this.conquistas = Integer.parseInt(conquistas);
        } 
    }

    public void setPublishers(String publishers) {
        this.publishers = removerEspacosIniciais(formatar(publishers,0));
    }

    public void setDevelopers(String developers) {
        this.developers = removerEspacosIniciais(formatar(developers,0));
    }

    public void setCategorias(String categorias) {
        this.categorias = formatar(categorias,0);
    }

    public void setGeneros(String generos) {
        this.generos = formatar(generos,1);
    }

    public void setTags(String tags) {
        this.tags = formatar(tags,1);
    }

    //metodos get
    public int getId() {
        return this.id;
    }

    public String getName() {
        return this.name;
    }

    public String getDate() {
        return this.date;
    }

    public int getJogadores() {
        return this.jogadores;
    }

    public float getPreco() {
        return this.preco;
    }

    public String[] getLinguas() {
        return this.linguas;
    }

    public int getNotaEspecial() {
        return this.notaEspecial;
    }

    public float getNotaUsuario() {
        return this.notaUsuario;
    }

    public int getConquistas() {
        return this.conquistas;
    }

    public String[] getPublishers() {
        return this.publishers;
    }

    public String[] getDevelopers() {
        return this.developers;
    }

    public String[] getCategorias() {
        return this.categorias;
    }

    public String[] getGeneros() {
        return this.generos;
    }

    public String[] getTags() {
        return this.tags;
    }

    //funções auxiliares
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

    public String[] removerEspacosIniciais(String[] array) {
        if (array == null) {
            return null;
        }
        
        String[] resultado = new String[array.length];
        
        for (int i = 0; i < array.length; i++) {
            if (array[i] != null) {
                // Remove apenas espaços do início usando replaceFirst
                resultado[i] = array[i].replaceFirst("^\\s+", "");
            } else {
                resultado[i] = null;
            }
        }
        
        return resultado;
    }

    public String printElementosMultiplos(String [] array, int aux){ //função para auxiliar o print
        String result = "[";
        for(int i = 0; i < array.length; i++) {
            result += array[i];
            if(i < array.length - 1 && aux == 0) {
                result += ",";
            }
            else if(i < array.length - 1 && aux == 1) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

    public String[] formatar(String entrada, int tipo) { //função que formata os casos que tem mais de 1 elemento em uma parte
        int virgulas = 0;
        for(int i = 0; i < entrada.length(); i++) {
            char c = entrada.charAt(i);
            if(c == ',') {
                virgulas++;
            }
        }
        String resp[] = new String[virgulas + 1];
        String aux = "";
        int contador = 0;
        if(tipo == 1){
            for(int i = 0; i < entrada.length(); i++) {
                char c = entrada.charAt(i); 
                if(c == ',') {
                    resp[contador] = aux;
                    contador++;
                    aux = "";
                }
                else {
                    if(!(c == '[' || c == ']')) {
                        aux += c;
                    } 
                }
            }
        }else{
            for(int i = 0; i < entrada.length(); i++) {
                char c = entrada.charAt(i); 
                if(c == ',') {
                    resp[contador] = aux;
                    contador++;
                    aux = "";
                }
                else {
                    if(!(c == '[' || c == ']' || c == '\'')) {
                        aux += c;
                    } 
                }
            }
        }
        resp[contador] = aux;
        return resp;
    }

    public String printResultado() { //metodo print final
        return ("=> " + id + " ## " + name + " ## " + date + " ## " + jogadores + " ## " + preco + " ## " + printElementosMultiplos(linguas,0) + " ## " + notaEspecial + " ## " + notaUsuario + " ## " + conquistas + " ## " + printElementosMultiplos(publishers,1) + " ## " + printElementosMultiplos(developers,1) + " ## " + printElementosMultiplos(categorias,1) + " ## " + printElementosMultiplos(generos,1) + " ## " + printElementosMultiplos(tags,1) + " ##");
    }
}

public class Main{

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

    public static void sets(Game game, String array[]){ //função de set tudo dos objetos
        game.setId(array[0]);
        game.setNome(array[1]);
        game.setData(array[2]);
        game.setJogadores(array[3]);
        game.setPreco(array[4]);
        game.setLinguas(array[5]);
        game.setNotaEspecial(array[6]);
        game.setNotaUsuario(array[7]);
        game.setConquistas(array[8]);
        game.setPublishers(array[9]);
        game.setDevelopers(array[10]);
        game.setCategorias(array[11]);
        game.setGeneros(array[12]);
        game.setTags(array[13]);
    }

    public static void main(String []args) throws FileNotFoundException{
        //declaração scanners (teclado e arquivo)
        Scanner scanner = new Scanner(System.in);
        File arq = new File("games.csv");
        Scanner scannerArq = new Scanner(arq);

        Game game[] = new Game[2000]; // array que vai guardar os nossos jogos
        int jogos = 0;

        //System.out.println("teste1");

        // Pular o cabeçalho
        if (scannerArq.hasNextLine()) {
            scannerArq.nextLine();
        }

        while(scannerArq.hasNextLine()) { //loop que vai ler linha por linha

            String entrada = scannerArq.nextLine();

            String array[] = new String[14]; 
            String aux = "";
            int contador = 0;
            boolean aspas = false;

            for(int i = 0; i<entrada.length(); i++){ //loop que vai até o final da linha, dividindo ela em partes
                char c = entrada.charAt(i);

                if(c == '"'){
                    aspas = !aspas;
                
                }else if(c == ',' && !aspas){
                    array[contador] = aux;
                    contador++;
                    aux = "";
                }else{
                    aux = aux + c;
                }
            }

            array[contador] = aux;

            //cria o objeto jogo e chama função de setar tudo
            game[jogos] = new Game();
            sets(game[jogos], array);
            jogos++;
            //System.out.println("teste3");
        }

        //System.out.println("teste");
        String flag = "FIM"; //string de termino
		boolean continuar = true; //flag booleana
        
	    while (continuar) { //loop para continuar até encontrar o FIM
	        String busca = scanner.nextLine();

	        if (compare(busca, flag)) { //verifica ocorrencia do FIM e decide se o programa acaba
            	continuar = false;
        	}else{
                int Busca = Integer.parseInt(busca);
                for(int i = 0; i < jogos; i++) {
                    if(Busca == game[i].getId()) {
                        System.out.println(game[i].printResultado());
                        
                        i = jogos;
                    }
                }
	        }

	    }
        scanner.close();
        scannerArq.close();
    }
}