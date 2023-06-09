#include <iostream>
using namespace std;

const int N = 9; // ukuran grid Sudoku
const int UNASSIGNED = 0; // nilai yang menunjukkan kotak kosong

// fungsi untuk mencetak grid Sudoku
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

// fungsi untuk memeriksa apakah suatu nilai dapat diisi pada suatu posisi di grid Sudoku
bool isSafe(int grid[N][N], int row, int col, int num) {
    // periksa apakah nilai num telah digunakan pada baris yang sama
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }
    
    // periksa apakah nilai num telah digunakan pada kolom yang sama
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }
    
    // periksa apakah nilai num telah digunakan pada kotak 3x3 yang sama
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (grid[i][j] == num) {
                return false;
            }
        }
    }
    
    // jika tidak ada konflik, nilai num dapat diisi pada posisi (row, col)
    return true;
}

// fungsi untuk menyelesaikan grid Sudoku menggunakan brute force
bool solveBruteForce(int grid[N][N], int row, int col) {
    // periksa apakah semua kotak telah diisi
    if (row == N) {
        return true;
    }
    
    // periksa apakah kotak saat ini kosong
    if (grid[row][col] != UNASSIGNED) {
        if (col == N-1) {
            if (solveBruteForce(grid, row+1, 0)) {
                return true;
            }
        } else {
            if (solveBruteForce(grid, row, col+1)) {
                return true;
            }
        }
        return false;
    }
    
    // mencoba semua nilai dari 1 hingga 9 pada kotak saat ini
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (col == N-1) {
                if (solveBruteForce(grid, row+1, 0)) {
                    return true;
                }
            } else {
                if (solveBruteForce(grid, row, col+1)) {
                    return true;
                }
            }
            grid[row][col] = UNASSIGNED;
        }
    }
    
    // jika tidak ada nilai yang dapat diisi pada kotak saat ini, kembali ke kotak sebelumnya
    return false;
}

int main() {
    int n;
	printf("Masukkan jumlah grid: ");
	cin >> n;
	int grid[N][N];
	printf("Masukkan angka untuk setiap kotak, gunakan 0 untuk kotak kosong:\n");
	for (int row = 0; row < n; row++) {
	    for (int col = 0; col < n; col++) {
	        cin >> grid[row][col];
	    }
	}
	
	if (solveBruteForce(grid, 0, 0)) {
	    printf("Solusi:\n");
	    printGrid(grid);
	} else {
	    printf("Tidak ada solusi yang mungkin.\n");
	}
	
	return 0;
}

