#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

char buffer1[255];
char buffer2[255];
char buffer3[255];
char buffer4[255];
char CPUloadbuffer[255];

//získanie hostname z /proc/sys/kernel/hostname
char * getHostName(){
    memset(buffer1, 0, sizeof(char)*255);
    FILE* filePointer1 = fopen("/proc/sys/kernel/hostname", "r");
    if(filePointer1 == NULL){
        fprintf(stderr, "Chyba pri zisťovaní názvu serveru!\n");
        exit(1);
    }
    fgets(buffer1, 255, filePointer1);
    fclose(filePointer1);
    return buffer1;
}

//získanie informací o CPU z /proc/cpuinfo
char * getCPUName(){

    memset(buffer2, 0, sizeof(char)*255);
    FILE* filePointer2 = popen("cat /proc/cpuinfo | grep \"model name\" | head -n 1 | cut -d' ' -f3-","r");

    if(filePointer2 == NULL){
        fprintf(stderr, "Chyba pri zisťovaní názvu CPU!\n");
        exit(1);
    }

    fgets(buffer2, 255, filePointer2);

    int status = pclose(filePointer2);
    if (status == -1) {
        fprintf(stderr, "Chyba pri zisťovaní názvu CPU!\n");
        exit(1);
    }

    return buffer2;
}


//Získanie aktuálneho zaťaženia serveru z /proc/stat
char * getCPULoad(){
    memset(buffer3, 0, sizeof(char)*255);
    memset(buffer4, 0, sizeof(char)*255);

    FILE* filePointer3 = fopen("/proc/stat", "r");
    if(filePointer3 == NULL){
        fprintf(stderr, "Chyba pri zisťovaní zaťaženia serveru!\n");
        exit(1);
    }
    fgets(buffer3, 255, filePointer3);

    fclose(filePointer3);

    sleep(1); //1 sekunda sleep


    FILE* filePointer4 = fopen("/proc/stat", "r");
    if(filePointer4 == NULL){
        fprintf(stderr, "Chyba pri zisťovaní zaťaženia serveru!\n");
        exit(1);
    }
    fgets(buffer4, 255, filePointer4);
    fclose(filePointer4);

    char prevUser[255];
    char prevNice[255];
    char prevSystem[255];
    char prevIdle[255];
    char prevIOwait[255];
    char prevIrq[255];
    char prevSoftirq[255];
    char prevSteal[255];
    char prevGuest[255];
    char prevGuest_nice[255];

    long prevUserNum = 0;
    long prevNiceNum = 0;
    long prevSystemNum = 0;
    long prevIdleNum = 0;
    long prevIOwaitNum = 0;
    long prevIrqNum = 0;
    long prevSoftirqNum = 0;
    long prevStealNum = 0;
    long prevGuestNum = 0;
    long prevGuest_niceNum = 0;

    int i = 0;
    int thing = 0;
    int lastwasspace = 0;

    //spracovanie riadku sa mohlo určite dať spraviť aj na menej riadkov, ale toto jednoduché manuálne parsnutie bolo napísané za minútku
    while(buffer3[i] != '\0')
    {
        if (!isdigit(buffer3[i]) && buffer3[i] != ' '){
            i++;
        }else{
            if(buffer3[i] == ' '){
                if(lastwasspace == 0){
                    thing++;
                }
                lastwasspace = 1;
                i++;
            }else{
                lastwasspace = 0;
                if (isdigit(buffer3[i])){
                    if(thing == 1){
                        prevUser[prevUserNum++] = buffer3[i++];
                    }else if(thing == 2){
                        prevNice[prevNiceNum++] = buffer3[i++];
                    }else if(thing == 3){
                        prevSystem[prevSystemNum++] = buffer3[i++];
                    }else if(thing == 4){
                        prevIdle[prevIdleNum++] = buffer3[i++];
                    }else if(thing == 5){
                        prevIOwait[prevIOwaitNum++] = buffer3[i++];
                    }else if(thing == 6){
                        prevIrq[prevIrqNum++] = buffer3[i++];
                    }else if(thing == 7){
                        prevSoftirq[prevSoftirqNum++] = buffer3[i++];
                    }else if(thing == 8){
                        prevSteal[prevStealNum++] = buffer3[i++];
                    }else if(thing == 9){
                        prevGuest[prevGuestNum++] = buffer3[i++];
                    }else if(thing == 10){
                        prevGuest_nice[prevGuest_niceNum++] = buffer3[i++];
                    }else{
                        fprintf(stderr, "CPUload information error!\n");
                        exit(1);
                    }
                }
            }
        }
    }
    prevUser[prevUserNum++] = '\0';
    prevNice[prevNiceNum++] = '\0';
    prevSystem[prevSystemNum++] = '\0';
    prevIdle[prevIdleNum++] = '\0';
    prevIOwait[prevIOwaitNum++] = '\0';
    prevIrq[prevIrqNum++] = '\0';
    prevSoftirq[prevSoftirqNum++] = '\0';
    prevSteal[prevStealNum++] = '\0';
    prevGuest[prevGuestNum++] = '\0';
    prevGuest_nice[prevGuest_niceNum++] = '\0';

    char User[255];
    char Nice[255];
    char System[255];
    char Idle[255];
    char IOwait[255];
    char Irq[255];
    char Softirq[255];
    char Steal[255];
    char Guest[255];
    char Guest_nice[255];

    long UserNum = 0;
    long NiceNum = 0;
    long SystemNum = 0;
    long IdleNum = 0;
    long IOwaitNum = 0;
    long IrqNum = 0;
    long SoftirqNum = 0;
    long StealNum = 0;
    long GuestNum = 0;
    long Guest_niceNum = 0;

    i = 0;
    thing = 0;
    lastwasspace = 0;

    while(buffer4[i] != '\0')
    {
        if (!isdigit(buffer4[i]) && buffer4[i] != ' '){
            i++;
        }else{
            if(buffer4[i] == ' '){
                if(lastwasspace == 0){
                    thing++;
                }
                lastwasspace = 1;
                i++;
            }else{
                lastwasspace = 0;
                if (isdigit(buffer4[i])){
                    if(thing == 1){
                        User[UserNum++] = buffer4[i++];
                    }else if(thing == 2){
                        Nice[NiceNum++] = buffer4[i++];
                    }else if(thing == 3){
                        System[SystemNum++] = buffer4[i++];
                    }else if(thing == 4){
                        Idle[IdleNum++] = buffer4[i++];
                    }else if(thing == 5){
                        IOwait[IOwaitNum++] = buffer4[i++];
                    }else if(thing == 6){
                        Irq[IrqNum++] = buffer4[i++];
                    }else if(thing == 7){
                        Softirq[SoftirqNum++] = buffer4[i++];
                    }else if(thing == 8){
                        Steal[StealNum++] = buffer4[i++];
                    }else if(thing == 9){
                        Guest[GuestNum++] = buffer4[i++];
                    }else if(thing == 10){
                        Guest_nice[Guest_niceNum++] = buffer4[i++];
                    }else{
                        fprintf(stderr, "CPUload information error!\n");
                        exit(1);
                    }
                }
            }
        }

    }
    User[UserNum++] = '\0';
    Nice[NiceNum++] = '\0';
    System[SystemNum++] = '\0';
    Idle[IdleNum++] = '\0';
    IOwait[IOwaitNum++] = '\0';
    Irq[IrqNum++] = '\0';
    Softirq[SoftirqNum++] = '\0';
    Steal[StealNum++] = '\0';
    Guest[GuestNum++] = '\0';
    Guest_nice[Guest_niceNum++] = '\0';

    long long minPokojStav = strtoll(prevIdle, NULL, 10) + strtoll(prevIOwait, NULL, 10);
    long long PokojStav = strtoll(Idle, NULL, 10) + strtoll(IOwait, NULL, 10);

    long long minPracujuciStav = strtoll(prevUser, NULL, 10) + strtoll(prevNice, NULL, 10) + strtoll(prevSystem, NULL, 10) + strtoll(prevIrq, NULL, 10) + strtoll(prevSoftirq, NULL, 10) + strtoll(prevSteal, NULL, 10);
    long long PracujuciStav = strtoll(User, NULL, 10) + strtoll(Nice, NULL, 10) + strtoll(System, NULL, 10) + strtoll(Irq, NULL, 10) + strtoll(Softirq, NULL, 10) + strtoll(Steal, NULL, 10);

    long long minTotal =  minPokojStav + minPracujuciStav;
    long long Total = PokojStav + PracujuciStav;

    long long TotalInTimeSpan = Total - minTotal;
    long long TotalIdleInTimeSpan = PokojStav - minPokojStav;

    //finálny výpočet zaťaženia a prevod na percentá
    long long CPULoad = ((((double)TotalInTimeSpan - (double)TotalIdleInTimeSpan)/(double)TotalInTimeSpan)*100);

    memset(CPUloadbuffer, 0, 255);
    sprintf(CPUloadbuffer, "%lld%%", CPULoad);

    return CPUloadbuffer;
}


int main (int argc, const char * argv[]) {

    int welcome_socket;
    struct sockaddr_in sa;
    struct sockaddr_in sa_client;
    int port_number;

    if (argc != 2) {
        fprintf(stderr,"Nesprávne argumenty!\n");
        exit(EXIT_FAILURE);
    }

    port_number = atoi(argv[1]);
    if(port_number < 0 || port_number > 65535){
        fprintf(stderr,"Nesprávne číslo portu! (0-65635)\n");
        exit(EXIT_FAILURE);
    }

    socklen_t sa_client_len=sizeof(sa_client);

    if ((welcome_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("Chyba pri vytváraní socketu!");
        exit(EXIT_FAILURE);
    }

    int reuse = 1;
    if (setsockopt(welcome_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt SO_REUSEADDR FAILED");
#ifdef SO_REUSEPORT
    if (setsockopt(welcome_socket, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt SO_REUSEPORT FAILED");
#endif

    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(port_number);


    if ((bind(welcome_socket, (struct sockaddr*)&sa, sizeof(sa))) < 0)
    {
        perror("Binding error!");
        exit(EXIT_FAILURE);
    }

    if ((listen(welcome_socket, 10)) < 0)
    {
        perror("Listening error!");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        int client_socket = accept(welcome_socket, (struct sockaddr*)&sa_client, &sa_client_len);

        if (client_socket > 0)
        {
            char buff[1024] = {0};
            //zaujíma nás len hlavička tak by mal stačiť recv aj bez cyklenia a kontrloly celého prijatia správy
            int rec = recv(client_socket, buff, 1024,0);
            if (rec < 0){
                perror("Receiving error!");
                exit(EXIT_FAILURE);
            }

            char* sprava = strtok(buff, " ");

            if(strcmp(sprava, "GET")){
                memset(buff, 0, 1024);
                sprintf(buff, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain;\r\n\r\nERROR 400 BAD REQUEST\n");
            }else{
                sprava = strtok(NULL, " ");
                if(!strcmp(sprava, "/hostname")){

                    memset(buff, 0, 1024);
                    sprintf(buff, "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n%s",getHostName());
                }else if(!strcmp(sprava, "/cpu-name")){
                    memset(buff, 0, 1024);
                    sprintf(buff, "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n%s",getCPUName());
                }else if(!strcmp(sprava, "/load")){
                    memset(buff, 0, 1024);
                    sprintf(buff, "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n%s\n",getCPULoad());
                }else{
                    memset(buff, 0, 1024);
                    sprintf(buff, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain;\r\n\r\nERROR 400 BAD REQUEST\n");
                }
                }
            send(client_socket, buff, strlen(buff), 0);
        }
        close(client_socket);
    }
}
