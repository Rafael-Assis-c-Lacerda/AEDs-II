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

public class binaria {
    public static int comparacoes = 0;

    public static int sort(Game array[], int n) {
        int swaps = 0;
    
        //Alterar o vetor ignorando a posicao zero
        Game[] tmp = new Game[n+1]; // Cria o array temporário 1-indexado
        for(int i = 0; i < n; i++){
            tmp[i+1] = array[i]; // Copia de 'ordenados' (0-index) para 'tmp' (1-index)
        }

        //Contrucao do heap
        for(int tamHeap = 2; tamHeap <= n; tamHeap++){
            swaps = swaps + construir(tamHeap,tmp);
        }

        //Ordenacao propriamente dita
        int tamHeap = n;
        while(tamHeap > 1){
            swap(1, tamHeap--, tmp);
            swaps++;
            swaps = swaps + reconstruir(tamHeap,tmp);
        }

        //Copiar os dados ordenados de 'tmp' de volta para 'array' ('ordenados')
        for(int i = 0; i < n; i++){
            array[i] = tmp[i+1]; // Copia de 'tmp' (1-index) para 'ordenados' (0-index)
        }

        return swaps;
   }

    public static boolean isMaior(Game a, Game b) {
        comparacoes++;
        if (a.getJogadores() > b.getJogadores()) {
            
            return true;
        } else if (a.getJogadores() < b.getJogadores()) {
            return false;
        } else {
        // Desempate: Se jogadores são iguais, compara pelo ID
            comparacoes++;
            return a.getId() > b.getId();
        }
    }


   public static int construir(int tamHeap, Game array []){
        int swaps = 0;

        for(int i = tamHeap; i > 1 && isMaior(array[i], array[i/2]); i /= 2){
            swap(i, i/2, array);
            swaps++;
        }

        return swaps;
   }


   public static int reconstruir(int tamHeap, Game array[]){
        int swaps = 0;

        int i = 1;
        while(i <= (tamHeap/2)){
            int filho = getMaiorFilho(i, tamHeap, array);
            if(isMaior(array[filho], array[i])){ // (array[filho] > array[i])
                swap(i, filho,array);
                swaps++;
                i = filho;
            }else{
                i = tamHeap;
            }
        }
        return swaps;
   }

    public static int getMaiorFilho(int i, int tamHeap , Game array[]){
        int filho;
        if (2*i == tamHeap || isMaior(array[2*i], array[2*i+1])){ // (array[2*i] > array[2*i+1])
            filho = 2*i;
        } else {
            filho = 2*i + 1;
        }
        return filho;
    }

   public static void swap(int i, int j, Game array[]) {
		Game temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}

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

    public static long now() {
        return System.nanoTime();
    }

    public static void main(String []args) throws FileNotFoundException{
        long inicio, fim;

        inicio = now();

        //declaração scanners (teclado e arquivo)
        Scanner scanner = new Scanner(System.in);
        File arq = new File("/tmp/games.csv");
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

        Game ordenados [] = new Game[2000];
        int n = 0;

	    while (continuar) { //loop para continuar até encontrar o FIM
	        String busca = scanner.nextLine();

	        if (compare(busca, flag)) { //verifica ocorrencia do FIM e decide se o programa acaba
            	continuar = false;
        	}else{
                int Busca = Integer.parseInt(busca);
                for(int i = 0; i < jogos; i++) {
                    if(Busca == game[i].getId()) {
                        ordenados[n] = game[i];
                        n++;

                        i = jogos;
                    }
                }
	        }

	    }

        int swaps = sort(ordenados,n);

		continuar = true; //flag booleana

        while (continuar) { //loop para continuar até encontrar o FIM
	        String busca = scanner.nextLine();

	        if (compare(busca, flag)) { //verifica ocorrencia do FIM e decide se o programa acaba
            	continuar = false;
        	}else{
                //int Busca = Integer.parseInt(busca);
                for(int i = 0; i < jogos; i++) {
                    if(compare(busca, ordenados[i].getName())) {
                        comparacoes++;
                        System.out.println("SIM");
                        
                        i = jogos;
                    }else{
                        comparacoes = comparacoes + 2;
                        System.out.println("NAO");
                    }
                }
	        }

	    }

        for(int i = 0; i < n; i++) {
            System.out.println(ordenados[i].printResultado());
        }

        scanner.close();
        scannerArq.close();

        fim = now();

        //Geração de Log (acho que é pra fazer isso)

        double tempoMs = (fim - inicio) / 1_000_000.0;
        String matricula = "885033";
        
        //Nome do txt que sera criado
        String nomeArquivo = matricula + "_binaria.txt"; 
        
        try (PrintWriter writer = new PrintWriter(new FileWriter(nomeArquivo))) {
            writer.printf("%s\t%s\t%d\n", matricula,tempoMs, comparacoes);
        } catch (IOException e) {
            System.err.println("Erro ao escrever o arquivo de log: " + e.getMessage());
        }
        
        //Fim Geração de Log

        //prints no console para conferir algumas coisas

        //System.out.println("Esse e o numero de swaps:" + swaps);
        //System.out.println("Esse e o numero de comparacoes:" + heapsort.comparacoes);
        //System.out.printf("Tempo execucao desde a leitura do arquivo até a ordenacao e print: %.3f ms.\n", (fim - inicio) / 1_000_000.0);
    }
}
