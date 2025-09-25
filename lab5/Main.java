import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Main {
    static Scanner scanner = new Scanner(System.in);

    //função swap
    public static void swap(int [] array, int i, int j) {
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}


    //diferentes quicksorts
    public static void quicksort(int [] array,int esq, int dir){
        int i = esq, j = dir;

        Random rand = new Random();
        int pivoIndex = rand.nextInt(dir - esq + 1) + esq;

        int pivo = array[pivoIndex];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  quicksort(array, esq, j);
        if (i < dir)  quicksort(array, i, dir);
    }

    public static void quicksortFirst(int [] array,int esq, int dir){
        int i = esq, j = dir;
        int pivo = array[esq];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  quicksort(array, esq, j);
        if (i < dir)  quicksort(array, i, dir);
    }

    public static void quicksortLast(int [] array,int esq, int dir){
        int i = esq, j = dir;
        int pivo = array[dir];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  quicksort(array, esq, j);
        if (i < dir)  quicksort(array, i, dir);
    }

    public static int median(int [] array,int esq, int dir){
        int mid = (esq + dir) / 2;
    
        int a = array[esq];
        int b = array[mid];
        int c = array[dir];
        
        if (a > b) {
            if (a < c) return esq;
            else if (b > c) return mid;
            else return dir;
        } else {
            if (b < c) return mid;
            else if (a > c) return esq;
            else return dir; 
        }
    }

    public static void quicksortMedian(int [] array,int esq, int dir){
        int i = esq, j = dir;
        int pivo = array[median(array, esq, dir)];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  quicksort(array, esq, j);
        if (i < dir)  quicksort(array, i, dir);
    }

    // Gera arrays para teste
    public static int[] generateRandomArray(int size) {
        Random rand = new Random();
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = rand.nextInt(size * 2);
        }
        return array;
    }

    public static int[] generateSortedArray(int size) {
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = i;
        }
        return array;
    }

    public static int[] generateAlmostSortedArray(int size) {
        int[] array = generateSortedArray(size);
        Random rand = new Random();
        int swaps = Math.max(1, size / 100);
        for (int i = 0; i < swaps; i++) {
            int idx1 = rand.nextInt(size);
            int idx2 = rand.nextInt(size);
            swap(array, idx1, idx2);
        }
        return array;
    }

    // Função para clonar array para evitar alterar o original durante testes
    public static int[] cloneArray(int[] original) {
        return Arrays.copyOf(original, original.length);
    }
    public static void main (String[]args){
        //criação do array e escolha do tamanho
        int[] array;
        int size = 1000;

        //gera o array original

        array = generateRandomArray(size);
        //array = generateSortedArray(size);
        //array = generateAlmostSortedArray(size);


        //faz a ordenação com o quicksort com pivo aleatorio
        long start = System.nanoTime();

        int[] copyForRandomPivot = cloneArray(array);
        quicksort(copyForRandomPivot, 0, copyForRandomPivot.length - 1);

        long end = System.nanoTime();
        long duration = end - start;  // duração em nanossegundos
        System.out.println("Quicksort aleatorio:" + size);
        System.out.println("Tempo decorrido: " + duration / 1_000_000.0 + " ms");


        start = System.nanoTime();

        //faz a ordenação com o quicksort com pivo aleatorio
        start = System.nanoTime();

        int[] copyForRandomPivot = cloneArray(array);
        quicksort(copyForRandomPivot, 0, copyForRandomPivot.length - 1);

        end = System.nanoTime();
        duration = end - start;  // duração em nanossegundos
        System.out.println("Quicksort aleatorio:" + size);
        System.out.println("Tempo decorrido: " + duration / 1_000_000.0 + " ms");


        start = System.nanoTime();

        //faz a ordenação com o quicksort com pivo aleatorio
        start = System.nanoTime();

        int[] copyForRandomPivot = cloneArray(array);
        quicksort(copyForRandomPivot, 0, copyForRandomPivot.length - 1);

        end = System.nanoTime();
        duration = end - start;  // duração em nanossegundos
        System.out.println("Quicksort aleatorio:" + size);
        System.out.println("Tempo decorrido: " + duration / 1_000_000.0 + " ms");


        start = System.nanoTime();

        

        scanner.close();
    }    
}
