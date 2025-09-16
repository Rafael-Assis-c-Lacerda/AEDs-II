import java.util.Scanner;

    class Participantes{
        public String nome;
        public int O;
        public int P;
        public int B;
    }

public class Main{
    static Scanner scanner = new Scanner(System.in);

    public static void bubbleSort(Participantes [] participante, int n){
        boolean trocou = true;
        int i = 0;
        while(i<n-1 && trocou){
            trocou = false;
            for(int j = 0; j<n-i-1;j++){
                if(participante[j].O<participante[j+1].O){
                    Participantes temp = participante[j];
                    participante[j] = participante[j+1];
                    participante[j+1] = temp;
                    trocou=true;
                }else if(participante[j].O==participante[j+1].O){
                    if(participante[j].P<participante[j+1].P){
                        Participantes temp = participante[j];
                        participante[j] = participante[j+1];
                        participante[j+1] = temp;
                        trocou=true;
                    }else if(participante[j].P==participante[j+1].P){
                        if(participante[j].B<participante[j+1].B){
                            Participantes temp = participante[j];
                            participante[j] = participante[j+1];
                            participante[j+1] = temp;
                            trocou=true;
                        }else if(participante[j].B==participante[j+1].B){
                            for(int k = 0; k<participante[j].nome.length();k++){
                                if(participante[j].nome.charAt(k)<participante[j+1].nome.charAt(k)){
                                    Participantes temp = participante[j];
                                    participante[j] = participante[j+1];
                                    participante[j+1] = temp;
                                    trocou=true;
                                }
                            }
                    }
                    }
                }
            }
            i++;
        }
    }

    public static void main(String [] args){
        int n = scanner.nextInt();

        Participantes [] participante = new Participantes [n];

        for(int i = 0; i<n;i++){
            participante[i] = new Participantes();  // inicializa o objeto

            participante[i].nome = scanner.next();
            participante[i].O = scanner.nextInt();
            participante[i].P = scanner.nextInt();
            participante[i].B = scanner.nextInt();
        }

        bubbleSort(participante, n);

        for(int j = 0; j<n; j++){
            System.out.println(participante[j].nome + " " +
                               participante[j].O + " " +
                               participante[j].P + " " +
                               participante[j].B);
        }
        scanner.close();
    }
}