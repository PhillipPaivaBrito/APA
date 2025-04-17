#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

class solver {
    public:

    int custtotal = 0;
    std::vector<std::vector<int>> rotas;

    int numero_de_voos,
        numero_de_pistas;

    std::vector <int> r;//termpo minimo para iniciar operação
    std::vector <int> c;//custo para completar operação
    std::vector <int> p;//custo de espera
    std::vector<std::vector<int>> t;//tempo de espera entre j e i

    std::vector<int> list; // termpo minimo para iniciar operação

    solver(int numero_de_voos, int numero_de_pistas,std::vector<int> &r,std::vector<int> &c, std::vector<int> &p, std::vector<std::vector<int>> &t){
        this-> numero_de_voos = numero_de_voos;
        this->numero_de_pistas = numero_de_pistas;
        this->r = r;
        this->c = c;
        this->p = p;
        this->t = t;
        this->list.swap(r);
        makePlaciment();
    }
    void makePlaciment(){
        //fazer heuristica para alocar os voos nas pistas
        //alocar os voos nas pistas de acordo com o tempo minimo para iniciar operação
        //alocar os voos nas pistas de acordo com o custo para completar operação
        //alocar os voos nas pistas de acordo com o custo de espera

        rotas.resize(numero_de_pistas);
        int i = 0;
        do{
            for(int j = 0; j < numero_de_pistas; j++,i++){
                if(i == numero_de_voos){
                    std::cout << std::endl << "Todos os voos alocados" << std::endl;
                    break;
                }else{
                    if(int(this->rotas[j].size()) < 1){
                        this->rotas[j].push_back(findshorterindex());
                    }else{
                        //aqui vai outro criterio de alocação
                        //alocar o voo na pista que tem o menor tempo de espera

                        this->rotas[j].push_back(findshorterindex());
                    }
                }
                
            }
        }while(i < numero_de_voos);
        std::cout << std::endl << "Rotas: " << std::endl;
        for(int i = 0; i < numero_de_pistas; i++){
            std::cout << "Pista " << i+1 << ": ";
            for(int j = 0; j < int(rotas[i].size()); j++){
                std::cout << rotas[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        calcvalue();
        
    }

    int findshorterindex(){
        int menor = 0;
        for (int i = 1; i < numero_de_voos; i++){
            //std::cout << "list[i]: " << this->list[i] << std::endl;
            if(this->list[i] < this->list[menor]){
                menor = i;
                
            }
        }
        //std::cout <<std::endl << "menor: " << menor;
        this->list[menor] = std::numeric_limits<int>::max(); // marca o menor como maximo para não ser escolhido novamente
        return menor;
    }

    void calcvalue(){
        
        //Multa = Valor Multa por Minuto *(Tempo de inıcio do pouso ou decolagem − Tempo de liberação do voo)
        //considerando que os primeiros voos sempre pousam sem esperar
        for(int i = 0; i < numero_de_pistas; i++){// para cada pista
        int timePD = 0; // tempo que o voo vai esperar para pousar ou decolar
        std::cout << timePD << " custo atual: "<< this->custtotal << std::endl;
            for(int j = 1; j < int(rotas[i].size()); j++){
                //std::cout << getr(rotas[i][j - 1]) << " "<< getc(rotas[i][j - 1]) << " " << gett(rotas[i][j - 1], rotas[i][j])<< " ";
                timePD += getr(rotas[i][j - 1]) + getc(rotas[i][j - 1]) + gett(rotas[i][j - 1], rotas[i][j]);
                this->custtotal +=  getp(this->rotas[i][j])*(timePD - getr(this->rotas[i][j]));
                std::cout << timePD << " custo atual: "<< this->custtotal << std::endl;
            }
        }
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
};

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
    std::ifstream myfile(arquivo + "n3m10A.txt"); //std::ifstream myfile(argv[1]);
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
    std::cout << std::endl << "Custos total: " << s.custtotal << std::endl;
    return 0;
}