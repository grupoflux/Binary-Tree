# include <stdio.h>
# include <string.h>
# include <curl/curl.h>


int main() {

    char linha[10000];    
        
    CURL *curl;
    CURLcode res;

    FILE *dados;

    
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    dados = fopen("teste.csv","w");

    if (curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://m9963ywzsg.execute-api.us-east-1.amazonaws.com/default/queryInHouse?nome=Gustavo");
        
        // recolhendo os dados dentro da URL
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, dados);

        #ifdef SKIP_PEER_VERIFICATION
            curl_easy_setopt(curl, CURLOPT_SSL_VERFYPEER, 0L);
        #endif

        #ifdef SKIP_HOSTNAME_VERIFICATION
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        #endif

        res = curl_easy_perform(curl);
                        
        fprintf(dados, "%s\n");
                
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        
        curl_easy_cleanup(curl);
    }

    
    curl_global_cleanup();

    fclose(dados);    

    return 0; 
}

