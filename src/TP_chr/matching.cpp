#include "matching.hpp"

std::ostream& operator<<(std::ostream& os, double** con){

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            os << con[i][j] << " ";
        }
        os << "\n";
    }

    os << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, int** con){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            os << con[i][j] << " ";
        }
        os << "\n";
    }

    os << "\n";
    return os;
}

double min(int n, double* dist){
    double val = __INT64_MAX__;
    for(int i = 0; i < n; i++){
        val = std::min(val, dist[i]);
    }
    return val;
}

void step1(int n, double** dist, int& step){
    for(int i = 0; i < n; i++) {
        auto smallest = min(n, dist[i]);
        if (smallest > 0){
            for(int j = 0; j < n; j++){
                dist[i][j] -= smallest;
            }
        }      
    }
    
    for (int j=0; j<n; j++) {
        double minval = __INT64_MAX__;
        for (int i=0; i<n; i++) {
            minval = std::min(minval, dist[i][j]);
        }
        
        if (minval > 0) {
            for (int i=0; i<n; ++i) {
                dist[i][j] -= minval;
            }
        }
    }
   
    step = 2;
}

inline void clear_covers(int n, int* cover){
    for (int i = 0; i < n; i++) cover[i] = 0;
}

void step2(int n, double** dist, int** M, int* RowCover, int* ColCover, int& step){
    
    for (int r=0; r<n; r++){
        for (int c=0; c<n; c++){
            if (dist[r][c] == 0){
                if (RowCover[r] == 0 && ColCover[c] == 0) {
                    M[r][c] = 1;
                    RowCover[r] = 1;
                    ColCover[c] = 1;
                }
            }
        }
    }
    clear_covers(n, RowCover);
    clear_covers(n, ColCover);
    
    step = 3;
}

void step3(int n, int** M, int* ColCover, int& step){
    int colcount = 0;
    
    for (int r=0; r<n; r++){
        for (int c=0; c<n; c++){
            if (M[r][c] == 1){
                ColCover[c] = 1;
            }
        }
    }
            
    for(int i = 0; i < n; i++){
        if(ColCover[i] == 1)
            colcount++;
    }
    
    if (colcount >= n) {
        step = 7;
    }
    else {
        step = 4;
    }
}

void find_a_zero(int n, int& row, int& col, double** dist, int* RowCover, int* ColCover){
    int r = 0;
    int c = 0;
    row = -1;
    col = -1;
    bool done = false;
    
    while (!done) {
        c = 0;
        while (true) {
            if (dist[r][c] == 0 && RowCover[r] == 0 && ColCover[c] == 0) {
                row = r;
                col = c;
                done = true;
            }
            c++;
            if (c >= n || done){
                break;
            }
        }
        r += 1;
        if (r >= n){
            done = true;
        }
    }
}

bool star_in_row(int n, int row, int** M){
    for (int c = 0; c < n; c++){
        if (M[row][c] == 1){
            return true;
        }
    }
    
    return false;
}

void find_star_in_row(int n, int row, int& col, int** M){
    col = -1;
    for (int c = 0; c < n; c++){
        if (M[row][c] == 1){
            col = c;
        }
    }
}

void step4(int n, double** dist, int** M, int* RowCover, int* ColCover, int& path_row_0, int& path_col_0, int& step){
    int row = -1;
    int col = -1;
    bool done = false;

    while (!done){
        find_a_zero(n, row, col, dist, RowCover, ColCover);
        
        if (row == -1){
            done = true;
            step = 6;
        }
        else {
            M[row][col] = 2;
            if(star_in_row(n, row, M)) {
                find_star_in_row(n, row, col, M);
                RowCover[row] = 1;
                ColCover[col] = 0;
            }
            else {
                done = true;
                step = 5;
                path_row_0 = row;
                path_col_0 = col;
            }
        }
    }
}

void find_star_in_col(int n, int c, int& r, int** M)
{
    r = -1;
    for (int i = 0; i < n; i++){
        if (M[i][c] == 1){
            r = i;
        }
    }
}

void find_prime_in_row(int n, int r, int& c, int** M){
    for (int j = 0; j < n; j++){
        if (M[r][j] == 2){
            c = j;
        }
    }
}

void augment_path(int** path, int path_count, int** M){
    for (int p = 0; p < path_count; p++){
        if (M[path[p][0]][path[p][1]] == 1){
            M[path[p][0]][path[p][1]] = 0;
        }else{
            M[path[p][0]][path[p][1]] = 1;
        }
    }
}

void erase_primes(int n, int** M){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (M[i][j] == 2){
                M[i][j] = 0;
            }   
        }
    }
}

void step5(int n, int** path, int path_row_0, int path_col_0, int** M, int* RowCover, int* ColCover, int& step){
    int r = -1;
    int c = -1;
    int path_count = 1;
    
    path[path_count - 1][0] = path_row_0;
    path[path_count - 1][1] = path_col_0;
    
    bool done = false;
    while (!done) {
        find_star_in_col(n, path[path_count - 1][1], r, M);
        if (r > -1) {
            path_count += 1;
            path[path_count - 1][0] = r;
            path[path_count - 1][1] = path[path_count - 2][1];
        } else {
            done = true;
        }
        
        if (!done) {
            find_prime_in_row(n, path[path_count - 1][0], c, M);
            path_count += 1;
            path[path_count - 1][0] = path[path_count - 2][0];
            path[path_count - 1][1] = c;
        }
    }
    
    augment_path(path, path_count, M);
    clear_covers(n, RowCover);
    clear_covers(n, ColCover);
    erase_primes(n, M);
    
    step = 3;
}

void find_smallest(int n, double& minval, double** matrix, int* RowCover, int* ColCover){
    for (int r = 0; r < n; r++){
        for (int c = 0; c < n; c++){
           if (RowCover[r] == 0 && ColCover[c] == 0){
                if (minval > matrix[r][c]){    
                    minval = matrix[r][c];
                }
           }
        }
    }
}

void step6(int n, double** matrix, int* RowCover, int* ColCover, int& step){
    double minval = __INT64_MAX__;
    find_smallest(n, minval, matrix, RowCover, ColCover);
    
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) {
            if (RowCover[r] == 1){
                matrix[r][c] += minval;
            }
            if (ColCover[c] == 0){
                matrix[r][c] -= minval;
            }
    }
    
    step = 4;
}

double output_solution(int n, double** original, int** M){
    double res = 0;
    
    for (int j = 0; j < n; j++){
        for (int i = 0; i < n; i++){
            if(M[i][j]){
                res += original[i][j];
            }
        }
    }
            
    return res;
}

bool hungarian(int n, double** original, int** M, time_t start){  

    double** matrix = new double*[n];
    for(int i = 0; i < n; i++){
        matrix[i] = new double[n];
        for(int j = 0; j < n; j++){
            matrix[i][j] = original[i][j];
        }
    }
    
    int* RowCover = new int[n];
    int* ColCover = new int[n];
    
    int path_row_0, path_col_0;
    
    int** path = new int*[n+1];
    for(int i = 0; i < n+1; i++){
        path[i] = new int[2];
        for(int j = 0; j < 2; j++){
            path[i][j] = 0;
        }
    }
    
    bool done = false;
    int step = 1;
    while (!done) {
        if(time(NULL) - start > TIME_LIMIT){
            return true;
        }
        switch (step) {
            case 1:
                step1(n, matrix, step);
                break;
            case 2:
                step2(n, matrix, M, RowCover, ColCover, step);
                break;
            case 3:
                step3(n, M, ColCover, step);
                break;
            case 4:
                step4(n, matrix, M, RowCover, ColCover, path_row_0, path_col_0, step);
                break;
            case 5:
                step5(n, path, path_row_0, path_col_0, M, RowCover, ColCover, step);
                break;
            case 6:
                step6(n, matrix, RowCover, ColCover, step);
                break;
            case 7:
                done = true;
                break;
            default:
                done = true;
                break;
        }
    }
    return false;
}