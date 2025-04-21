#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>

class Neighborhood {
public:
    // Movimento 1: Troca dois voos entre pistas diferentes
    static bool swapBetweenTracks(std::vector<std::vector<int>>& solution, int track1, int pos1, int track2, int pos2) {
        if (track1 >= int(solution.size()) || track2 >= int(solution.size()) || 
            pos1 >= int(solution[track1].size()) || pos2 >= int(solution[track2].size())) {
            return false;
        }
        
        std::swap(solution[track1][pos1], solution[track2][pos2]);
        return true;
    }

    // Movimento 2: Move um voo para outra posição na mesma pista
    static bool insertInSameTrack(std::vector<std::vector<int>>& solution, int track, int oldPos, int newPos) {
        if (track >= int(solution.size()) || oldPos >= int(solution[track].size()) || newPos > int(solution[track].size())) {
            return false;
        }
        
        if (oldPos == newPos || oldPos == newPos - 1) {
            return false;
        }
        
        int flight = solution[track][oldPos];
        solution[track].erase(solution[track].begin() + oldPos);
        solution[track].insert(solution[track].begin() + newPos, flight);
        return true;
    }

    // Movimento 3: Move um voo para outra pista
    static bool moveToOtherTrack(std::vector<std::vector<int>>& solution, int oldTrack, int pos, int newTrack) {
        if (oldTrack >= int(solution.size()) || newTrack >= int(solution.size()) || pos >= int(solution[oldTrack].size())) {
            return false;
        }
        
        int flight = solution[oldTrack][pos];
        solution[oldTrack].erase(solution[oldTrack].begin() + pos);
        solution[newTrack].push_back(flight);
        return true;
    }
};

class VND {
private:
    int numero_de_voos;
    int numero_de_pistas;
    std::vector<int> r;
    std::vector<int> c;
    std::vector<int> p;
    std::vector<std::vector<int>> t;
    
    int calculateSolutionCost(const std::vector<std::vector<int>>& solution) {
        int totalCost = 0;
        
        for (const auto& track : solution) {
            if (track.empty()) continue;
            
            int currentTime = r[track[0]] + c[track[0]];
            
            for (size_t i = 1; i < track.size(); ++i) {
                int flight = track[i];
                int prevFlight = track[i-1];
                
                // Calcula o tempo de início considerando o tempo de espera
                int startTime = std::max(r[flight], currentTime + t[prevFlight][flight]);
                int delay = startTime - r[flight];
                totalCost += p[flight] * delay;
                
                currentTime = startTime + c[flight];
            }
        }
        
        return totalCost;
    }

public:
    VND(int num_voos, int num_pistas, const std::vector<int>& r_vec, 
        const std::vector<int>& c_vec, const std::vector<int>& p_vec, 
        const std::vector<std::vector<int>>& t_mat)
        : numero_de_voos(num_voos), numero_de_pistas(num_pistas),
          r(r_vec), c(c_vec), p(p_vec), t(t_mat) {}
    
    void improveSolution(std::vector<std::vector<int>>& initialSolution) {
        int k = 1;
        const int maxNeighborhoods = 3;
        int currentCost = calculateSolutionCost(initialSolution);
        
        while (k <= maxNeighborhoods) {
            bool improved = false;
            auto bestSolution = initialSolution;
            int bestCost = currentCost;
            
            // Explora toda a vizinhança k
            switch (k) {
                case 1: // Swap entre pistas
                    for (int t1 = 0; t1 < numero_de_pistas; ++t1) {
                        for (int p1 = 0; p1 < int(initialSolution[t1].size()); ++p1) {
                            for (int t2 = t1+1; t2 < numero_de_pistas; ++t2) {
                                for (int p2 = 0; p2 < int(initialSolution[t2].size()); ++p2) {
                                    auto neighbor = initialSolution;
                                    if (Neighborhood::swapBetweenTracks(neighbor, t1, p1, t2, p2)) {
                                        int neighborCost = calculateSolutionCost(neighbor);
                                        if (neighborCost < bestCost) {
                                            bestCost = neighborCost;
                                            bestSolution = neighbor;
                                            improved = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                    
                case 2: // Insert na mesma pista
                    for (int t = 0; t < numero_de_pistas; ++t) {
                        for (int p1 = 0; p1 < int(initialSolution[t].size()); ++p1) {
                            for (int p2 = 0; p2 <= int(initialSolution[t].size()); ++p2) {
                                if (p1 == p2 || p1 == p2 - 1) continue;
                                auto neighbor = initialSolution;
                                if (Neighborhood::insertInSameTrack(neighbor, t, p1, p2)) {
                                    int neighborCost = calculateSolutionCost(neighbor);
                                    if (neighborCost < bestCost) {
                                        bestCost = neighborCost;
                                        bestSolution = neighbor;
                                        improved = true;
                                    }
                                }
                            }
                        }
                    }
                    break;
                    
                case 3: // Move para outra pista
                    for (int t1 = 0; t1 < numero_de_pistas; ++t1) {
                        for (int p = 0; p < int(initialSolution[t1].size()); ++p) {
                            for (int t2 = 0; t2 < numero_de_pistas; ++t2) {
                                if (t1 == t2) continue;
                                auto neighbor = initialSolution;
                                if (Neighborhood::moveToOtherTrack(neighbor, t1, p, t2)) {
                                    int neighborCost = calculateSolutionCost(neighbor);
                                    if (neighborCost < bestCost) {
                                        bestCost = neighborCost;
                                        bestSolution = neighbor;
                                        improved = true;
                                    }
                                }
                            }
                        }
                    }
                    break;
            }
            
            if (improved) {
                initialSolution = bestSolution;
                currentCost = bestCost;
                k = 1; // Volta para a primeira vizinhança
            } else {
                k++; // Vai para a próxima vizinhança
            }
        }
    }
};

class solver {
public:
    int custtotal;
    std::vector<std::vector<int>> rotas;
    int numero_de_voos, numero_de_pistas;
    std::vector<int> r, c, p;
    std::vector<std::vector<int>> t;
    std::vector<int> list;

    solver(int numero_de_voos, int numero_de_pistas, std::vector<int>& r, 
           std::vector<int>& c, std::vector<int>& p, std::vector<std::vector<int>>& t)
        : numero_de_voos(numero_de_voos), numero_de_pistas(numero_de_pistas),
          r(r), c(c), p(p), t(t) {
        this->list = r;
        makePlaciment();

        // Aplicar VND para melhorar a solução inicial
        VND vnd(numero_de_voos, numero_de_pistas, r, c, p, t);
        vnd.improveSolution(rotas);
        
        // Recalcular custo total após VND
        custtotal = 0;
        for(int i = 0; i < numero_de_pistas; i++) {
            custtotal += calcValueLine(i);
        }
    }
    void makePlaciment(){
        rotas.resize(numero_de_pistas);
        int i = 0;
        do{
            for(int j = 0; j < numero_de_pistas; j++,i++){
                if(i == numero_de_voos){
                    //std::cout << std::endl << "Todos os voos alocados" << std::endl;
                    break;
                }else{
                    //std::cout << std::endl << this->rotas[j].size() << std::endl;
                    if((this->rotas[j].size()) < 1){
                        this->rotas[j].push_back(findSmallestValue());
                    }else{
                        //aqui vai outro criterio de alocação
                        //alocar o voo na pista que tem o menor tempo de espera
                        this->rotas[j].push_back(greedy(j));
                    }
                } 
            }
        }while(i < numero_de_voos);

        for(int i = 0; i < numero_de_pistas; i++){
            this->custtotal += calcValueLine(i);
        }
        std::cout << std::endl;
    }

    int findSmallestValue(){
        int menor = 0;
        for (int i = 1; i < numero_de_voos; i++){
            //std::cout << "list[i]: " << this->list[i] << std::endl;
            if(this->list[i] < this->list[menor] && this->list[i] >= 0){
                menor = i;
                
            }
        }
        
        this->list[menor] = std::numeric_limits<int>::max()/2; // marca o menor como maximo/2 para não ser escolhido novamente
        //std::cout << "menor index: " << menor << " valor: " << getr(menor) << " " << this->list[menor] <<std::endl;
        return menor;
    }

    int greedy(int j){
        
        int menor = 0;
        //std::cout << std::endl << "pista: " << j+1 << " index: " << rotas[j].size()-1 << " to " << std::endl;
        //std::cout << std::endl << "index " << 0 
        //                       << " valor: " << getr(0) 
        //                       << " c: " << getc(0)
        //                       << " t: " << gett(j,0) 
        //                       << " custo: " << this->list[0] + getc(0) + gett(j,0);

        for (int i = 1; i < numero_de_voos; i++){
            if((this->list[i] +      getc(rotas[j].size()-1) + gett(i    ,rotas[j].size()-1)) < 
               (this->list[menor] +  getc(rotas[j].size()-1) + gett(menor,rotas[j].size()-1))){
                menor = i;
            }
            //std::cout << std::endl << "index " << i 
                                   //<< " valor: " << getr(i) 
                                   //<< " c: " << getc(rotas[j].size()-1)
                                   //<< " t: " << gett(i,rotas[j].size()-1)
                                   //<< " custo: " << this->list[i] + getc(rotas[j].size()-1) + gett(i,rotas[j].size()-1);
        }
        
        this->list[menor] = (std::numeric_limits<int>::max()/2); // marca o menor como maximo para não ser escolhido novamente
        //std::cout << std::endl << "menor: " << menor << " valor: " << getr(menor) << std::endl;
        return menor;
    }

    int calcValueLine(int pista) {
        int costLine = 0;
        
        if (rotas[pista].empty()) return 0;
        
        // Primeiro voo na pista começa no seu tempo de liberação
        int currentTime = r[rotas[pista][0]] + c[rotas[pista][0]];
        
        for (size_t j = 1; j < rotas[pista].size(); j++) {
            int flight = rotas[pista][j];
            int prevFlight = rotas[pista][j-1];
            
            // Tempo de início é o máximo entre:
            // 1. Tempo de liberação do voo atual
            // 2. Tempo de término do voo anterior + tempo de espera obrigatório
            int startTime = std::max(r[flight], currentTime + t[prevFlight][flight]);
            
            // Calcula a multa por atraso
            int delay = startTime - r[flight];
            costLine += p[flight] * delay;
            
            // Atualiza o tempo atual para o término deste voo
            currentTime = startTime + c[flight];
        }
    
    return costLine;
}

    int getr(int row){
        return this->r[row];
    }
    int getc(int row){
        return this->c[row];
    }
    int getp(int row){
        return this->p[row];
    }
    int gett(int row, int col){
        return this->t[row][col];
    }
};//fim da classe solver

int main(int argc, char *argv[]){

    std::string arquivo = "../instancias_teste/";
    int content;

    int numero_de_voos,
        numero_de_pistas;

    std::vector <int> r;//tempo minimo para iniciar operação
    std::vector <int> c;//custo para completar operação
    std::vector <int> p;//custo de espera
    std::vector<std::vector<int>> t;//tempo de espera entre j e i
    //abrir arquivo
    std::ifstream myfile(arquivo + "teste.txt"); //std::ifstream myfile(argv[1]);
    if(argc > 1){
        myfile.close(); // fecha o arquivo
        myfile.clear(); // limpa o estado do arquivo
        myfile.open(arquivo + argv[1]);
    }
      
    if (!(myfile.is_open()))  // Se houve erro na abertura
    {
        std::cout << "Problemas na abertura do arquivo\n" << myfile.is_open();
        return 0;
    }
    std::cout << "Arquivo aberto com sucesso\n";
    myfile >> numero_de_voos;
    myfile >> numero_de_pistas;

    std::cout << numero_de_voos << std::endl << numero_de_pistas << std::endl<<std::endl;

    for(int i = 0; i < numero_de_voos; i++){// leitura tempo minimo para iniciar operação
        myfile >> content;
        r.push_back(content);
        std::cout << r.back() <<' ';
    }
    std::cout<<std::endl;
    for(int i = 0; i < numero_de_voos; i++){// leitura dos custo para completar operação
        myfile >> content;
        c.push_back(content);
        std::cout << c.back() <<' ';
    }
    std::cout<<std::endl;
    for(int i = 0; i < numero_de_voos; i++){// leitura dos custo de espera
        myfile >> content;
        p.push_back(content);
        std::cout << p.back() <<' ';
    }
    std::cout<<std::endl<<std::endl;;

    t.resize(numero_de_voos, std::vector<int>(numero_de_voos)); // Redimensiona t para ser uma matriz numero_de_voos x numero_de_voos
    
    for(int i = 0; i < numero_de_voos; i++){// leitura da matriz de tempo de espera entre j e i
        for(int j = 0; j < numero_de_voos; j++){
            myfile >> content;
            t[i][j] = content;
            std::cout << t[i][j]<<' ';
        }
        std::cout<<std::endl;
    }
    myfile.close(); // fecha o arquivo
    solver s(numero_de_voos, numero_de_pistas, r, c, p, t);
    std::cout << std::endl << "Custos total: " << s.custtotal;
    std::cout << std::endl << "Rotas: " << std::endl;
        for(int i = 0; i < numero_de_pistas; i++){
            std::cout << "Pista " << i+1 << ": ";
            for(int j = 0; j < int(s.rotas[i].size()); j++){
                std::cout << s.rotas[i][j] + 1 << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        return 1;
}